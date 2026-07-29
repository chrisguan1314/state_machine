#pragma once

enum class StateMachineOperationType : uint8_t
{
    NONE_0,
    OPEN_1,
    ACTIVE_2,
    RESUME_3,
    FINISH_4,
    EXIT_5,
};

enum class StateMachineRecoverableType : uint8_t
{
    NONE_0,
    DOORS_OPENED_1,
};

enum class StateMachineUnrecoverableType : uint8_t
{
    NONE_0,
    DOORS_OPENED_TOO_LONG_1,
    CAMERA_FAULT_2,
    LIDAR_FAULT_3,
    RADAR_FAULT_4,
};

enum class StateMachineOverrideType : uint8_t
{
    NONE_0,
    STEERING_WHEEL_1,
    BRAKE_PEDAL_2,
};

class StateMachineEventBase
{
private:
    StateMachineOperationType operation_type_{StateMachineOperationType::NONE_0};
    StateMachineRecoverableType recoverable_type_{StateMachineRecoverableType::NONE_0};
    StateMachineUnrecoverableType unrecoverable_type_{StateMachineUnrecoverableType::NONE_0};
    StateMachineOverrideType override_type_{StateMachineOverrideType::NONE_0};
public:
    StateMachineEventBase() noexcept = default;
public:
    StateMachineOperationType GetOperationType() const noexcept
    {
        return operation_type_;
    }
    StateMachineRecoverableType GetRecoverableType() const noexcept
    {
        return recoverable_type_;
    }
    StateMachineUnrecoverableType GetUnrecoverableType() const noexcept
    {
        return unrecoverable_type_;
    }
    StateMachineOverrideType GetOverrideType() const noexcept
    {
        return override_type_;
    }
    void SetOperationType(StateMachineOperationType operation_type = StateMachineOperationType::NONE_0) noexcept
    {
        operation_type_ = operation_type;
    }
    void SetRecoverableType(StateMachineRecoverableType recoverable_type = StateMachineRecoverableType::NONE_0) noexcept
    {
        recoverable_type_ = recoverable_type;
    }
    void SetUnrecoverableType(StateMachineUnrecoverableType unrecoverable_type = StateMachineUnrecoverableType::NONE_0) noexcept
    {
        unrecoverable_type_ = unrecoverable_type;
    }
    void SetOverrideType(StateMachineOverrideType override_type = StateMachineOverrideType::NONE_0) noexcept
    {
        override_type_ = override_type;
    }
};

#if __cplusplus >= 202002L
template <typename T>
concept is_event_base = std::derived_from<T, StateMachineEventBase>;
#endif