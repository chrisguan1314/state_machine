#pragma once

#include "state_machine_event_base.h"

#include <memory>

class StateMachineInputBase
{
private:
    std::shared_ptr<StateMachineEventBase> event_sptr_{std::make_shared<StateMachineEventBase>()};
public:
    void Init()
    {
        InitReaders();
    }
public:
    virtual void InitReaders() = 0;
    virtual void UpdateEvent() = 0;
};