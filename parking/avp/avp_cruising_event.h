#include "../../base/state_machine_event_base.h"

namespace parking
{
enum class AvpCruisingEventType : uint8_t
{
    NONE_0,
    LOCATED_1,
    UNLOCATED_2,
    PREPARED_3,
    UNPREPARED_4,
    SWITCH_TO_PARKING_5,
    SUCCESS_6,
    FAILURE_7,
};
class AvpCruisingEvent : public StateMachineEventBase
{
private:
    AvpCruisingEventType avp_cruising_event_type_{AvpCruisingEventType::NONE_0};
public:
    AvpCruisingEvent() noexcept = default;
public:
    AvpCruisingEventType GetAvpCruisingEventType() const noexcept
    {
        return avp_cruising_event_type_;
    }
    void SetAvpCruisingEventType(AvpCruisingEventType avp_cruising_event_type = AvpCruisingEventType::NONE_0) noexcept
    {
        avp_cruising_event_type_ = avp_cruising_event_type;
    }
};
};
