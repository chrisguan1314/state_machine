#pragma once

#include "state_machine_event_base.h"
#include "state_machine_param_base.h"

#include <memory>

class StateMachineInputerBase
{
private:
    std::shared_ptr<StateMachineEventBase> event_sptr_{std::make_shared<StateMachineEventBase>()};
public:
    StateMachineInputerBase(std::shared_ptr<StateMachineEventBase> && event = std::make_shared<StateMachineEventBase>()) : event_sptr_(std::move(event))
    {

    }
public:
    void Init()
    {
        InitReaders();
    }
public:
    virtual void InitReaders() = 0;
    virtual void UpdateEvent() = 0;
};