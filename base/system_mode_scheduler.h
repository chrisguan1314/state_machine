#pragma once

#include <cstdint>
#include <chrono>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>

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
        /**
         * @brief 初始化系统子模式切换器及其转换条件。
         *
         * 当前仅注册由低阶人工驾驶模式切换至驾驶或泊车功能的入口；
         * 泊车功能的切换条件由对应状态机是否正在运行决定。
         */
        void InitSystemSwitcher()
        {
            if (system_switcher_ = std::make_unique<SystemSwitcher>())
            {
                system_switcher_->AddSwitchEntry(SystemSubMode::MANUL_LOW_0, SystemSubMode::PILOT_ACC_10, [this] {
                    return system_param_->GetPilotEnableParam().acc_enable_;
                });
                system_switcher_->AddSwitchEntry(SystemSubMode::MANUL_LOW_0, SystemSubMode::PILOT_LCC_11, [this] {
                    return system_param_->GetPilotEnableParam().lcc_enable_;
                });
                system_switcher_->AddSwitchEntry(SystemSubMode::MANUL_LOW_0, SystemSubMode::PARKING_APA_30, [] {
                    return parking::ApaStateSwitcher::IsRunning();
                });
                system_switcher_->AddSwitchEntry(SystemSubMode::MANUL_LOW_0, SystemSubMode::PARKING_APO_31, [] {
                    return parking::ApoStateSwitcher::IsRunning();
                });
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
        static SystemMode Convert(SystemSubMode sub_mode)
        {
            switch (sub_mode)
            {
            case SystemSubMode::MANUL_LOW_0:
            case SystemSubMode::MANUL_HIGH_1:
                return SystemMode::MANUL_0;
            case SystemSubMode::PILOT_ACC_10:
            case SystemSubMode::PILOT_LCC_11:
                return SystemMode::PILOT_1;
            case SystemSubMode::PARKING_APA_30:
            case SystemSubMode::PARKING_APO_31:
            case SystemSubMode::PARKING_AVM_32:
            case SystemSubMode::PARKING_AVP_MAPPING_33:
            case SystemSubMode::PARKING_AVP_CRUISING_34:
                return SystemMode::PARKING_2;
            case SystemSubMode::AS_AEB_50:
            case SystemSubMode::AS_AES_51:
            case SystemSubMode::AS_MEB_52:
            case SystemSubMode::AS_BSD_53:
                return SystemMode::ACTIVE_SAFETY_3;
            default:
                throw std::runtime_error("Unsupported system sub-mode");
                break;
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
                // 以当前子模式为起点，按已注册规则计算下一子模式。
                SystemSubMode next_sub_mode = GetSystemSubMode().GetCrnt();
                auto sub_table = system_switcher_->At(next_sub_mode);
                if (sub_table.has_value())
                {
                    for (const auto &entry : sub_table.value())
                    {
                        // 满足条件的目标子模式将作为本轮更新结果。
                        if (entry.second())
                        {
                            next_sub_mode = entry.first;
                            break;
                        }
                    }
                }
                sub_mode_.Update(next_sub_mode);
                system_mode_.Update(Convert(next_sub_mode));

                // 固定调度周期，避免循环持续占用 CPU。
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
            InitReadersAndWriters();
            InitParameters();
            InitSystemSwitcher();
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
        static SystemModeInfo<SystemMode> GetSystemMode()
        {
            return system_mode_;
        }
        /**
         * @brief 获取当前系统子模式信息。
         * @return 当前系统子模式的副本。
         */
        static SystemModeInfo<SystemSubMode> GetSystemSubMode()
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
        /** @brief 系统子模式转换规则管理器。 */
        std::unique_ptr<SystemSwitcher> system_switcher_{nullptr};
        /** @brief 执行模式调度循环的后台线程。 */
        std::unique_ptr<std::jthread> scheduler_thread_{nullptr};
        /** @brief APA 状态机引擎。 */
        std::unique_ptr<parking::ApaStateMachineEngine> apa_engine_{nullptr};
        /** @brief APO 状态机引擎。 */
        std::unique_ptr<parking::ApoStateMachineEngine> apo_engine_{nullptr};
        /** @brief AVP 巡航状态机引擎。 */
        std::unique_ptr<parking::AvpCruisingStateMachineEngine> avp_cruising_engine_{nullptr};
        /** @brief AVP 建图状态机引擎。 */
        std::unique_ptr<parking::AvpMappingStateMachineEngine> avp_mapping_engine_{nullptr};
    };

} // namespace function