#pragma once

#include "state_machine_action_base.h"
#include "state_machine_inputer_base.h"
#include "state_machine_switcher_base.h"

#include <memory>

template <typename Data, typename Param, typename Inputer, typename Switcher,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineParamBase, Param>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineInputerBase<Param>, Inputer>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineSwitcherBase<Data, Param, Inputer>, Switcher>>>
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
    virtual void UpdateAction(std::shared_ptr<Param> param, std::shared_ptr<Inputer> input, std::shared_ptr<Switcher> switcher) = 0;
};