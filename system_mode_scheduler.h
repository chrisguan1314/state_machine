#pragma once

#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace structure
{
namespace function
{

enum class SystemMode : std::uint8_t
{
    MANUL_0 = 0,
    PILOT_1,
    PARKING_2,
    ACTIVE_SAFETY_3
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


class SystemScheduler
{
public:
    bool SwitchMode(SystemMode target_mode)
    {
        ValidateMode(target_mode);
        if (current_mode_ != target_mode)
        {
            StopMode(current_mode_);
            current_mode_ = target_mode;
        }
        return true;
    }

    SystemMode GetCurrentMode() const noexcept
    {
        return current_mode_;
    }

    bool Start(ManualSubMode sub_mode)
    {
        SwitchMode(SystemMode::MANUL_0);
        return manual_state_machine_.Start(sub_mode);
    }

    bool Start(PilotSubMode sub_mode)
    {
        SwitchMode(SystemMode::PILOT_1);
        return pilot_state_machine_.Start(sub_mode);
    }

    bool Start(ParkingSubMode sub_mode)
    {
        SwitchMode(SystemMode::PARKING_2);
        return parking_state_machine_.Start(sub_mode);
    }

    bool Start(ActiveSafetySubMode sub_mode)
    {
        SwitchMode(SystemMode::ACTIVE_SAFETY_3);
        return active_safety_state_machine_.Start(sub_mode);
    }

    bool Stop(ManualSubMode sub_mode)
    {
        return manual_state_machine_.Stop(sub_mode);
    }

    bool Stop(PilotSubMode sub_mode)
    {
        return pilot_state_machine_.Stop(sub_mode);
    }

    bool Stop(ParkingSubMode sub_mode)
    {
        return parking_state_machine_.Stop(sub_mode);
    }

    bool Stop(ActiveSafetySubMode sub_mode)
    {
        return active_safety_state_machine_.Stop(sub_mode);
    }

    void StopMode(SystemMode mode)
    {
        switch (mode)
        {
        case SystemMode::MANUL_0:
            manual_state_machine_.StopAll();
            break;
        case SystemMode::PILOT_1:
            pilot_state_machine_.StopAll();
            break;
        case SystemMode::PARKING_2:
            parking_state_machine_.StopAll();
            break;
        case SystemMode::ACTIVE_SAFETY_3:
            active_safety_state_machine_.StopAll();
            break;
        default:
            break;
        }
    }

    void StopAll()
    {
        manual_state_machine_.StopAll();
        pilot_state_machine_.StopAll();
        parking_state_machine_.StopAll();
        active_safety_state_machine_.StopAll();
    }

    bool IsRunning(ManualSubMode sub_mode) const
    {
        return manual_state_machine_.IsRunning(sub_mode);
    }

    bool IsRunning(PilotSubMode sub_mode) const
    {
        return pilot_state_machine_.IsRunning(sub_mode);
    }

    bool IsRunning(ParkingSubMode sub_mode) const
    {
        return parking_state_machine_.IsRunning(sub_mode);
    }

    bool IsRunning(ActiveSafetySubMode sub_mode) const
    {
        return active_safety_state_machine_.IsRunning(sub_mode);
    }

    const SubFunctionStateMachine<ManualSubMode>& ManualStateMachine() const noexcept
    {
        return manual_state_machine_;
    }

    const SubFunctionStateMachine<PilotSubMode>& PilotStateMachine() const noexcept
    {
        return pilot_state_machine_;
    }

    const SubFunctionStateMachine<ParkingSubMode>& ParkingStateMachine() const noexcept
    {
        return parking_state_machine_;
    }

    const SubFunctionStateMachine<ActiveSafetySubMode>& ActiveSafetyStateMachine() const noexcept
    {
        return active_safety_state_machine_;
    }

private:
    static void ValidateMode(SystemMode mode)
    {
        if (mode > SystemMode::ACTIVE_SAFETY_3)
        {
            throw std::invalid_argument("invalid system mode");
        }
    }

    SystemMode current_mode_{SystemMode::MANUL_0};
    SubFunctionStateMachine<ManualSubMode> manual_state_machine_;
    SubFunctionStateMachine<PilotSubMode> pilot_state_machine_;
    SubFunctionStateMachine<ParkingSubMode> parking_state_machine_;
    SubFunctionStateMachine<ActiveSafetySubMode> active_safety_state_machine_;
};

}  // namespace function
}  // namespace structure