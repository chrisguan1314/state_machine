#pragma once

#include "state_machine_action_base.h"

#include <memory>

class StateMachineOutputBase
{
private:
    std::shared_ptr<StateMachineActionBase> action_sptr_{nullptr};
public:
    StateMachineOutputBase(std::shared_ptr<StateMachineActionBase> action = std::make_shared<StateMachineActionBase>()) : 
    action_sptr_(action)
    {
    }
public:
    void Init()
    {
        InitWriters();
    }
public:
    virtual void InitWriters() {};
    virtual void UpdateAction() {};
};