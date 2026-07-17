#pragma once

#include <map>
#include <algorithm>
#include <functional>

template <typename T>
class StateSwitchTable
{
public:
    using StateType = T;
    using SwitchFunction = std::function<bool(StateType)>;
    using SwitchSubTable = std::map<T, SwitchFunction>;
    using SwitchTable = std::map<T, SwitchSubTable>;
private:
    using StateList = std::vector<T>;
private:
    SwitchTable state_switch_table_;
public:
    void AddStateSwitch(T from_state, T to_state, SwitchFunction func)
    {
        state_switch_table_.at(from_state).at(to_state) = func;
    }
    void AddStateSwitch(T from_state, const SwitchSubTable& table)
    {
        if (state_switch_table_.find(from_state) != std::end(state_switch_table_))
        {
            std::for_each(std::begin(table), std::end(table), [this, from_state](auto item){
                state_switch_table_.at(from_state).at(item.first) = item.second; 
            });
        }
        else
        {
            state_switch_table_.insert({from_state, table});
        }
    }
    const StateList GetToStateList(T state) const noexcept
    {
        StateList list;
        auto sub_table = state_switch_table_.at(state);
        std::for_each(std::begin(sub_table), std::end(sub_table), [&list](auto item){
            list.push_back(item.first);
        });
        return list;
    }
    const SwitchSubTable& GetSwitchTable(T state) const noexcept
    {
        return state_switch_table_.at(state);
    }
};