#pragma once

#include "state_machine_action_base.h"
#include "state_machine_switcher_base.h"

#include <map>
#include <functional>

template <typename State, typename = typename std::enable_if_t<std::is_enum_v<State>>>
class StateMachineOutputerBase
{
public: 
    using StateType = State;
    using ActionFunction = std::function<void()>;
    using ActionTable = std::map<State, ActionFunction>;
private:
    std::shared_ptr<StateMachineActionBase> action_sptr_{nullptr};
    ActionTable action_table_{};
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
    virtual State GetCrntState() const noexcept = 0;
public:
    void UpdateAction()
    {
        auto crnt_state = GetCrntState();
        auto iter = action_table_.find(crnt_state);
        if (iter != action_table_.end())
        {
            iter->second();
        }
    }
protected:
    void AddAction(State state, ActionFunction func)
    {
        action_table_[state] = func;
    }
};