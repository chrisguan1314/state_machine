#pragma once

#include "state_machine_action_base.h"
#include "state_machine_switcher_base.h"

#include <map>
#include <functional>

template <typename State, typename Param, typename Inputer, typename Switcher,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineParamBase, Param>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineInputerBase, Inputer>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineSwitcherBase<State>, Switcher>>>
class StateMachineOutputerBase
{
public: 
    using StateType = State;
    using ParamType = Param;
    using InputerType = Inputer;
    using SwitcherType = Switcher;
    using ParamSPtr = std::shared_ptr<ParamType>;
    using InputerSPtr = std::shared_ptr<InputerType>;
    using SwitcherSPtr = std::shared_ptr<SwitcherType>;
    using ActionFunction = std::function<void(ParamSPtr, InputerSPtr, SwitcherSPtr)>;
    using ActionTable = std::map<State, ActionFunction>;
private:
    std::shared_ptr<StateMachineActionBase> action_sptr_{nullptr};
    ActionTable action_table_{ActionTable()};
public:
    StateMachineOutputerBase(std::shared_ptr<StateMachineActionBase> action = std::make_shared<StateMachineActionBase>()) : action_sptr_(action)
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
    void UpdateAction(const ParamSPtr& param, const InputerSPtr& input, const SwitcherSPtr& switcher)
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
};