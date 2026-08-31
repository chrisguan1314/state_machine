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

#include "parking/avp/cruising/avp_cruising_state_machine_engine.h"

namespace function
{

    enum class SystemMode : std::uint8_t
    {
        MANUL_0 = 0,
        PILOT_1,
        PARKING_2,
        ACTIVE_SAFETY_3
    };

    enum class SystemSubMode : std::uint8_t
    {
        // Manual sub-modes start from 0
        MANUL_LOW_0 = 0,
        MANUL_HIGH_1,
        // Pilot sub-modes start from 10 to avoid overlap with manual sub-modes
        PILOT_ACC_10 = 10,
        PILOT_LCC_11,
        // Parking sub-modes start from 30 to avoid overlap with other sub-modes
        PARKING_APA_30 = 30,
        PARKING_APO_31,
        PARKING_AVM_32,
        PARKING_AVP_33,
        // Active Safety sub-modes start from 50 to avoid overlap with other sub-modes
        AS_AEB_50 = 50,
        AS_AES_51,
        AS_MEB_52,
        AS_BSD_53
    };

    class SystemScheduler
    {
    public:
        SystemScheduler() = default;
        ~SystemScheduler() = default;

        SystemScheduler(const SystemScheduler &) = delete;
        SystemScheduler &operator=(const SystemScheduler &) = delete;
        SystemScheduler(SystemScheduler &&) = delete;
        SystemScheduler &operator=(SystemScheduler &&) = delete;

    private:
        void InitReadersAndWriters()
        {
            // 创建读写器
        }
        void InitParameters()
        {
            const std::string parameter_file_path = "path/to/parameter/file.json";
            if (system_param_ = std::make_unique<SystemParam>())
            {
                system_param_->LoadParameters(parameter_file_path);
            }
            else
            {
                throw std::runtime_error("Failed to create SystemParam instance.");
            }
        }
        void InitThread()
        {
            if (scheduler_thread_ = std::make_unique<std::jthread>([this](std::stop_token stop_token)
                                                               { Run(stop_token); }))
            {
                std::cout << "Scheduler thread initialized successfully." << std::endl;
            }
            else
            {
                throw std::runtime_error("Failed to initialize scheduler thread.");
            }
        }
    private:
        void EnablePilotFunctionality()
        {
            // Enable pilot functionality here
        }
        void EnableParkingFunctionality()
        {
            if (system_param_->GetParkingEnableParam().avp_cruising_enable_)
            {
                if (avp_cruising_engine_ = std::make_unique<parking::AvpCruisingStateMachineEngine>())
                {
                    avp_cruising_engine_->Init();
                    avp_cruising_engine_->Start();
                    std::cout << "AVP Cruising Engine initialized successfully." << std::endl;
                }
                else
                {
                    std::cerr << "Failed to initialize AVP Cruising Engine." << std::endl;
                }
            }
            // Enable parking functionality here
        }
        void EnableActiveSafetyFunctionality()
        {
            // Enable active safety functionality here
        }
    public:
        void Init()
        {
            // Initialize the system scheduler by setting up readers, writers, and loading parameters
            InitReadersAndWriters();
            //  Load the parameters from the parameter file
            InitParameters();
            // Initialize the scheduler thread
            InitThread();
        }
        void Setup()
        {
            EnablePilotFunctionality();
            EnableParkingFunctionality();
            EnableActiveSafetyFunctionality();  
        }
        void Run(std::stop_token stop_token)
        {
            while (!stop_token.stop_requested())
            {
                // Update system mode and sub-mode based on conditions
                // For demonstration, we will just set some dummy values
                sysmode_mode_.SetCrntState(SystemMode::PARKING_2);
                sysmode_sub_mode_.SetCrntState(SystemSubMode::PARKING_AVP_33);

                // Simulate some processing delay
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        static SystemModeInfo<SystemMode> GetSystemMode() noexcept
        {
            return sysmode_mode_;
        }
        static SystemModeInfo<SystemSubMode> GetSystemSubMode() noexcept
        {
            return sysmode_sub_mode_;
        }

    private:
        inline static SystemModeInfo<SystemMode> sysmode_mode_{};
        inline static SystemModeInfo<SystemSubMode> sysmode_sub_mode_{};

        std::unique_ptr<SystemParam> system_param_{nullptr};
        std::unique_ptr<std::jthread> scheduler_thread_{nullptr};
        
        std::unique_ptr<parking::AvpCruisingStateMachineEngine> avp_cruising_engine_{nullptr};
    };

} // namespace function