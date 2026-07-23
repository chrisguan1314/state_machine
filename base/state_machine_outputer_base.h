#pragma once

#include "state_machine_action_base.h"
#include "state_machine_inputer_base.h"
#include "state_machine_switcher_base.h"

#include <memory>
#include <map>
#include <functional>

template <typename State, typename Param, typename Inputer, typename Switcher,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineParamBase, Param>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineInputerBase<Param>, Inputer>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineSwitcherBase<State, Param, Inputer>, Switcher>>>
class StateMachineOutputerBase
{
public: 
    using ActionTable = std::map<State, std::function<void(std::shared_ptr<Param>, std::shared_ptr<Inputer>, std::shared_ptr<Switcher>)>>;
    using ParamSPtr = std::shared_ptr<Param>;
    using InputerSPtr = std::shared_ptr<Inputer>;
    using SwitcherSPtr = std::shared_ptr<Switcher>;
    using ActionFunction = std::function<void(ParamSPtr, InputerSPtr, SwitcherSPtr)>;
private:
    std::shared_ptr<StateMachineActionBase> action_sptr_{nullptr};
    ActionTable action_table_;
public:
    StateMachineOutputerBase(std::shared_ptr<StateMachineActionBase> action = std::make_shared<StateMachineActionBase>()) : 
    action_sptr_(action)
    {
    }
public:
    void Init()
    {
        InitWriters();
        InitActionTable();
    }
public:
    virtual void InitWriters() = 0;
    virtual void InitActionTable() = 0;
public:
    void UpdateAction(ParamSPtr param, InputerSPtr input, SwitcherSPtr switcher)
    {
        auto crnt_state = switcher->GetCrntState();
        auto iter = action_table_.find(crnt_state);
        if (iter != action_table_.end())
        {
            iter->second(param, input, switcher);
        }
    }
protected:
    void AddAction(State state, ActionFunction func)
    {
        action_table_[state] = func;
    }
    const ActionTable & GetActionTable() const noexcept
    {
        return action_table_;
    }
};