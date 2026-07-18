#pragma once

#include "state_machine_action_base.h"

#include <memory>

class StateMachineOutputBase
{
private:
    std::shared_ptr<StateMachineActionBase> action_sptr_{std::make_shared<StateMachineActionBase>()};
public:
    void Init()
    {
        InitWriters();
    }
public:
    virtual void InitWriters() = 0;
    virtual void UpdateAction() = 0;
};