#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <variant>
#include <thread>
#include <filesystem>

#include "system_mode_info.h"
#include "system_param.h"
#include "system_mode_enum.h"
#include "system_switcher.h"

#include "parking/apa/apa/apa_state_machine_engine.h"
#include "parking/apo/apo/apo_state_machine_engine.h"
#include "parking/avp/cruising/avp_cruising_state_machine_engine.h"
#include "parking/avp/mapping/avp_mapping_state_machine_engine.h"

namespace function
{
    /**
     * @brief 协调整车模式、子模式及各功能状态机的系统调度器。
     *
     * 该类以单例形式维护系统模式信息，并负责初始化调度线程、
     * 参数及已启用的驾驶、泊车和主动安全功能。
     */
    class SystemScheduler
    {
    public:
        /** @brief 禁止复制系统调度器。 */
        SystemScheduler(const SystemScheduler &) = delete;
        /** @brief 禁止复制赋值系统调度器。 */
        SystemScheduler &operator=(const SystemScheduler &) = delete;
        /** @brief 禁止移动系统调度器。 */
        SystemScheduler(SystemScheduler &&) = delete;
        /** @brief 禁止移动赋值系统调度器。 */
        SystemScheduler &operator=(SystemScheduler &&) = delete;
        /** @brief 销毁系统调度器及其持有的资源。 */
        ~SystemScheduler() = default;

        /**
         * @brief 获取系统调度器的唯一实例。
         * @return 指向唯一 SystemScheduler 实例的只读智能指针引用。
         */
        static const std::unique_ptr<SystemScheduler> &GetInstance()
        {
            static const std::unique_ptr<SystemScheduler> instance(new SystemScheduler());
            return instance;
        }

    private:
        /** @brief 构造系统调度器，仅允许通过 GetInstance() 创建。 */
        SystemScheduler() = default;

    private:
        /** @brief 初始化系统模式相关的读写器。 */
        void InitReadersAndWriters()
        {
            // 创建读写器
        }
        /** @brief 创建并加载系统参数。 */
        void InitParameters()
        {
            if (system_param_ = std::make_unique<SystemParam>("file.json"))
            {
                system_param_->LoadParameters();
            }
            else
            {
                throw std::runtime_error("[SystemScheduler] Failed to create SystemParam instance.");
            }
        }
        void InitSystemSwitcher()   
        {
            if (system_switcher_ = std::make_unique<SystemSwitcher>())
            {
                system_switcher_->AddSwitchEntry(SystemSubMode::MANUL_LOW_0, SystemSubMode::PILOT_ACC_10, [] { 
                    return true; 
                });
                system_switcher_->AddSwitchEntry(SystemSubMode::MANUL_LOW_0, SystemSubMode::PILOT_LCC_11, [] { 
                    return true; 
                });
                system_switcher_->AddSwitchEntry(SystemSubMode::MANUL_LOW_0, SystemSubMode::PARKING_APA_30, []{ 
                    return parking::ApaStateSwitcher::IsRunning();
                });
                system_switcher_->AddSwitchEntry(SystemSubMode::MANUL_LOW_0, SystemSubMode::PARKING_APO_31, []{
                     return parking::ApoStateSwitcher::IsRunning(); });
                std::cout << "[SystemScheduler] SystemSwitcher initialized successfully." << std::endl;
            }
            else
            {
                throw std::runtime_error("[SystemScheduler] Failed to initialize SystemSwitcher.");
            }
        }
        /** @brief 创建并启动系统模式调度线程。 */
        void InitThread()
        {
            if (scheduler_thread_ = std::make_unique<std::jthread>([this](std::stop_token stop_token)
                                                                   { Run(stop_token); }))
            {
                std::cout << "[SystemScheduler] Scheduler thread initialized successfully." << std::endl;
            }
            else
            {
                throw std::runtime_error("[SystemScheduler] Failed to initialize scheduler thread.");
            }
        }
        /** @brief 启用智能驾驶功能。 */
        void EnablePilotFunctionality()
        {
            // Enable pilot functionality here
        }
        /** @brief 根据参数启用 AVP 巡航和建图功能。 */
        void EnableParkingFunctionality()
        {
            if (system_param_->GetParkingEnableParam().apa_enable_)
            {
                if (apa_engine_ = std::make_unique<parking::ApaStateMachineEngine>())
                {
                    apa_engine_->Init();
                    apa_engine_->Start();
                    std::cout << "[SystemScheduler] APA Engine initialized successfully." << std::endl;
                }
                else
                {
                    std::cerr << "[SystemScheduler] Failed to initialize APA Engine." << std::endl;
                }
            }
            if (system_param_->GetParkingEnableParam().apo_enable_)
            {
                if (apo_engine_ = std::make_unique<parking::ApoStateMachineEngine>())
                {
                    apo_engine_->Init();
                    apo_engine_->Start();
                    std::cout << "[SystemScheduler] APO Engine initialized successfully." << std::endl;
                }
                else
                {
                    std::cerr << "[SystemScheduler] Failed to initialize APO Engine." << std::endl;
                }
            }
            if (system_param_->GetParkingEnableParam().avp_cruising_enable_)
            {
                if (avp_cruising_engine_ = std::make_unique<parking::AvpCruisingStateMachineEngine>())
                {
                    avp_cruising_engine_->Init();
                    avp_cruising_engine_->Start();
                    std::cout << "[SystemScheduler] AVP Cruising Engine initialized successfully." << std::endl;
                }
                else
                {
                    std::cerr << "[SystemScheduler] Failed to initialize AVP Cruising Engine." << std::endl;
                }
            }
            if (system_param_->GetParkingEnableParam().avp_mapping_enable_)
            {
                if (avp_mapping_engine_ = std::make_unique<parking::AvpMappingStateMachineEngine>())
                {
                    avp_mapping_engine_->Init();
                    avp_mapping_engine_->Start();
                    std::cout << "[SystemScheduler] AVP Mapping Engine initialized successfully." << std::endl;
                }
                else
                {
                    std::cerr << "[SystemScheduler] Failed to initialize AVP Mapping Engine." << std::endl;
                }
            }
            // Enable parking functionality here
        }
        /** @brief 启用主动安全功能。 */
        void EnableActiveSafetyFunctionality()
        {
            // Enable active safety functionality here
        }
        /**
         * @brief 将系统子模式转换为对应的系统模式。
         * @param sub_mode 要转换的系统子模式。
         * @return 与子模式对应的系统模式。
         */
        SystemMode Convert(SystemSubMode sub_mode)
        {
            static const std::unordered_map<SystemSubMode, SystemMode> sub_mode_to_mode_map = {
                {SystemSubMode::MANUL_LOW_0, SystemMode::MANUL_0},
                {SystemSubMode::MANUL_HIGH_1, SystemMode::MANUL_0},
                {SystemSubMode::PILOT_ACC_10, SystemMode::PILOT_1},
                {SystemSubMode::PILOT_LCC_11, SystemMode::PILOT_1},
                {SystemSubMode::PARKING_APA_30, SystemMode::PARKING_2},
                {SystemSubMode::PARKING_APO_31, SystemMode::PARKING_2},
                {SystemSubMode::PARKING_AVM_32, SystemMode::PARKING_2},
                {SystemSubMode::PARKING_AVP_MAPPING_33, SystemMode::PARKING_2},
                {SystemSubMode::PARKING_AVP_CRUISING_34, SystemMode::PARKING_2},
                {SystemSubMode::AS_AEB_50, SystemMode::ACTIVE_SAFETY_3},
                {SystemSubMode::AS_AES_51, SystemMode::ACTIVE_SAFETY_3},
                {SystemSubMode::AS_MEB_52, SystemMode::ACTIVE_SAFETY_3},
                {SystemSubMode::AS_BSD_53, SystemMode::ACTIVE_SAFETY_3}
            };
            if (sub_mode_to_mode_map.find(sub_mode) != std::end(sub_mode_to_mode_map))
            {
                return sub_mode_to_mode_map.at(sub_mode);
            }
            else
            {
                throw std::runtime_error("Unsupported system sub-mode");
            }
        }
        /**
         * @brief 执行系统模式调度循环。
         * @param stop_token 用于请求调度循环退出的停止令牌。
         */
        void Run(std::stop_token stop_token)
        {
            while (!stop_token.stop_requested())
            {
                // Update system mode and sub-mode based on conditions
                // For demonstration, we will just set some dummy values
                SystemSubMode next_sub_mode = GetSystemSubMode().GetCrnt();
                auto sub_table = system_switcher_->At(next_sub_mode);
                if (sub_table.has_value())
                {
                    for (const auto &entry : sub_table.value())
                    {
                        // Process each entry in the sub-table
                        if (entry.second())
                        {
                            next_sub_mode = entry.first;
                        }
                    }
                }

                sub_mode_.Update(next_sub_mode);
                system_mode_.Update(Convert(next_sub_mode));

                parking::AvpCruisingStateSwitcher::GetCrntState();

                // Simulate some processing delay
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    public:
        /**
         * @brief 初始化调度器依赖的读写器、参数和调度线程。
         * @throw std::runtime_error 参数或调度线程创建失败时抛出。
         */
        void Init()
        {
            // Initialize the system scheduler by setting up readers, writers, and loading parameters
            InitReadersAndWriters();
            //  Load the parameters from the parameter file
            InitParameters();
            // Initialize the system switcher
            InitSystemSwitcher();
            // Initialize the scheduler thread
            InitThread();
        }
        /** @brief 启用已配置的驾驶、泊车和主动安全功能。 */
        void Setup()
        {
            EnablePilotFunctionality();
            EnableParkingFunctionality();
            EnableActiveSafetyFunctionality();
        }
    public:
        /**
         * @brief 获取当前系统模式信息。
         * @return 当前系统模式的副本。
         */
        static SystemModeInfo<SystemMode> GetSystemMode() noexcept
        {
            return system_mode_;
        }
        /**
         * @brief 获取当前系统子模式信息。
         * @return 当前系统子模式的副本。
         */
        static SystemModeInfo<SystemSubMode> GetSystemSubMode() noexcept
        {
            return sub_mode_;
        }
    private:
        /** @brief 全局当前系统模式。 */
        inline static SystemModeInfo<SystemMode> system_mode_{};
        /** @brief 全局当前系统子模式。 */
        inline static SystemModeInfo<SystemSubMode> sub_mode_{};
    private:
        /** @brief 系统功能配置参数。 */
        std::unique_ptr<SystemParam> system_param_{nullptr};
        std::unique_ptr<SystemSwitcher> system_switcher_{nullptr};
        /** @brief 执行模式调度循环的后台线程。 */
        std::unique_ptr<std::jthread> scheduler_thread_{nullptr};
        /** @brief APA 状态机引擎。 */
        std::unique_ptr<parking::ApaStateMachineEngine> apa_engine_{nullptr};
        std::unique_ptr<parking::ApoStateMachineEngine> apo_engine_{nullptr};
        /** @brief AVP 巡航状态机引擎。 */
        std::unique_ptr<parking::AvpCruisingStateMachineEngine> avp_cruising_engine_{nullptr};
        /** @brief AVP 建图状态机引擎。 */
        std::unique_ptr<parking::AvpMappingStateMachineEngine> avp_mapping_engine_{nullptr};
    };

} // namespace function