#pragma once

#include "state_machine_action_base.h"
#include "state_machine_inputer_base.h"
#include "state_machine_switcher_base.h"

#include <memory>

class StateMachineOutputerBase
{
private:
    std::shared_ptr<StateMachineActionBase> action_sptr_{nullptr};
public:
    StateMachineOutputerBase(std::shared_ptr<StateMachineActionBase> action = std::make_shared<StateMachineActionBase>()) : 
    action_sptr_(action)
    {
    }
public:
    void Init()
    {
        InitWriters();
    }
public:
    virtual void InitWriters() = 0;
    virtual void UpdateAction() = 0;
};