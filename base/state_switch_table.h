#pragma once

#include "concept_base.h"
#include "state_machine_param_base.h"
#include "state_machine_inputer_base.h"

#include <map>
#include <memory>
#include <vector>
#include <concepts>
#include <algorithm>
#include <functional>
#include <type_traits>

#if __cplusplus >= 202002L
template <is_enum State, is_param_base Param, is_event_base Event, is_inputer_base<Param, Event> Inputer, typename Container = std::vector<State>>
#else
template <typename State, typename Param, typename Event, typename Inputer, typename Container = std::vector<State>,
typename = typename std::enable_if_t<std::is_enum_v<State>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineParamBase, Param>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineEventBase, Event>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineInputerBase<Param, Event>, Inputer>>>
#endif
class StateSwitchTable
{
public:
    using StateType = State;
    using ParamType = Param;
    using InputerType = Inputer;
    using StateList = Container;
    using SwitchFunction = std::function<bool(std::shared_ptr<ParamType>, std::shared_ptr<InputerType>)>;
    using SwitchSubTable = std::map<State, SwitchFunction>;
    using SwitchTable = std::map<State, SwitchSubTable>;
private:
    SwitchTable state_switch_table_;
public:
    void AddStateSwitch(StateType from_state, StateType to_state, SwitchFunction func)
    {
        if (state_switch_table_.find(from_state) != std::end(state_switch_table_))
        {
            auto & sub_table = state_switch_table_.at(from_state);
            sub_table[to_state] = func;
        }
        else
        {
            SwitchSubTable table = {{to_state, func}};
            state_switch_table_[from_state] = table;
        }
    }
    void AddStateSwitch(StateType from_state, const SwitchSubTable& table)
    {
        if (state_switch_table_.find(from_state) != std::end(state_switch_table_))
        {
            std::for_each(std::begin(table), std::end(table), [this, from_state](auto item){
                state_switch_table_.at(from_state).at(item.first) = item.second; 
            });
        }
        else
        {
            state_switch_table_[from_state] = table;
        }
    }
    const StateList GetToStateList(StateType state) const noexcept
    {
        StateList list;
        if (state_switch_table_.find(state) != std::end(state_switch_table_))
        {
            auto & sub_table = state_switch_table_.at(state);
            std::for_each(std::begin(sub_table), std::end(sub_table), [&list](auto item){
                list.push_back(item.first); 
            });
        }
        return list;
    }
    const StateList GetFromStateList(StateType state) const noexcept
    {
        StateList list;
        for (const auto& [from_state, sub_table] : state_switch_table_)
        {
            if (sub_table.find(state) != std::end(sub_table))
            {
                list.push_back(from_state);
            }
        }
        return list;
    }
    const SwitchSubTable& GetSubStateSwitchTable(StateType state) const noexcept
    {
        return state_switch_table_.at(state);
    }
    const SwitchTable& GetStateSwitchTable() const noexcept
    {
        return state_switch_table_;
    }
};