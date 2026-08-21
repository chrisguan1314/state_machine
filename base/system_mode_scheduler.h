#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <variant>
#include <thread>

#include "system_mode_info.h"

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
    MANUL_LOW_0 = 0,
    MANUL_HIGH_1,
    PILOT_ACC_10 = 10,
    PILOT_LCC_11,
    PARKING_APA_30 = 30,
    PARKING_APO_31,
    PARKING_AVM_32,
    PARKING_AVP_33,
    AS_AEB_50 = 50,
    AS_AES_51,
    AS_MEB_52,
    AS_BSD_53
};

enum class ManualSubMode : std::uint16_t
{
    NONE_0 = 0,
    MANUL_1 = 1
};

enum class PilotSubMode : std::uint16_t
{
    NONE_0 = 0,
    PILOT_1,
    ACC_2,
    LCC_3
};

enum class ParkingSubMode : std::uint16_t
{
    NONE_0 = 0,
    APA_1,
    RPA_2,
    AVP_3,
    AVM_4
};

enum class ActiveSafetySubMode : std::uint16_t
{
    NONE_0 = 0,
    AEB_1,
    AES_2,
    MEB_3,
    BSD_4
};

class SystemModeScheduler
{
public:
    SystemModeScheduler() = default;
    ~SystemModeScheduler() = default;
public:
    bool Init()
    {
        avp_cruising_engine_enable_ = true;
        scheduler_thread_ = std::jthread([this](std::stop_token stop_token) {
            Run(stop_token);
        });
        return true;
    }
    void Setup()
    {
        if (avp_cruising_engine_enable_)
        {
            avp_cruising_engine_ = std::make_unique<parking::AvpCruisingStateMachineEngine>();
        }
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
    SystemModeInfo<SystemMode> GetSystemMode() const noexcept
    {
        return sysmode_mode_;
    }
    SystemModeInfo<SystemSubMode> GetSystemSubMode() const noexcept
    {
        return sysmode_sub_mode_;
    }
private:
    SystemModeInfo<SystemMode> sysmode_mode_;
    SystemModeInfo<SystemSubMode> sysmode_sub_mode_;

    std::jthread scheduler_thread_;

    bool avp_cruising_engine_enable_{false};
    std::unique_ptr<parking::AvpCruisingStateMachineEngine> avp_cruising_engine_{nullptr};
};

}  // namespace function