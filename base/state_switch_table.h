#pragma once

#include <map>
#include <memory>
#include <type_traits>
#include <algorithm>
#include <functional>
#include <any>

#include "state_machine_param_base.h"
#include "state_machine_inputer_base.h"

template <typename T, typename Container = std::vector<T>, typename = typename std::enable_if_t<std::is_enum_v<T>>>
class StateSwitchTable
{
public:
    using StateType = T;
    using ToStateList = Container;
    using SwitchFunction = std::function<bool()>;
    using SwitchSubTable = std::map<T, SwitchFunction>;
    using SwitchTable = std::map<T, SwitchSubTable>;

private:
    SwitchTable state_switch_table_;

public:
    void AddStateSwitch(StateType from_state, StateType to_state, SwitchFunction &&func)
    {
        if (state_switch_table_.find(from_state) != std::end(state_switch_table_))
        {
            state_switch_table_.at(from_state)[to_state] = std::move(func);
        }
        else
        {
            state_switch_table_[from_state] = {{to_state, std::move(func)}};
        }
    }
    void AddStateSwitch(StateType from_state, SwitchSubTable &&table)
    {
        if (state_switch_table_.find(from_state) != std::end(state_switch_table_))
        {
            std::for_each(std::begin(table), std::end(table), [this, from_state](auto &&item)
                          { state_switch_table_.at(from_state).at(item.first) = std::move(item.second); });
        }
        else
        {
            state_switch_table_[from_state] = std::move(table);
        }
    }
    const ToStateList GetToStateList(StateType state) const noexcept
    {
        ToStateList list;
        auto & sub_table = state_switch_table_.at(state);
        std::for_each(std::begin(sub_table), std::end(sub_table), [&list](auto & item)
                      { list.push_back(item.first); });
        return list;
    }
    const SwitchSubTable &GetStateSwitchTable(StateType state) const noexcept
    {
        return state_switch_table_.at(state);
    }
    const SwitchTable &GetSwitchTable() const noexcept
    {
        return state_switch_table_;
    }
};