#pragma once

#include "state_machine_event_base.h"
#include "state_machine_param_base.h"

#include <memory>

class StateMachineInputer
{
public:
    void Init()
    {
        InitReaders();
    }
    
public:
    virtual void InitReaders() = 0;
    virtual void UpdateEvent() = 0;
};