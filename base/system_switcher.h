#pragma once

#include "system_mode_enum.h"

#include <functional>
#include <optional>
#include <map>

namespace function
{
    class SystemSwitcher
    {
    public:
        using SwitchFunction = std::function<bool()>;
        using SwitchSubTable = std::map<SystemSubMode, SwitchFunction>;
        using SwitchTable = std::map<SystemSubMode, SwitchSubTable>;

    private:
        SwitchTable switch_table_;

    public:
        SystemSwitcher() = default;
        ~SystemSwitcher() = default;
        SystemSwitcher(const SystemSwitcher &) = default;
        SystemSwitcher &operator=(const SystemSwitcher &) = default;
        SystemSwitcher(SystemSwitcher &&) = default;
        SystemSwitcher &operator=(SystemSwitcher &&) = default;
    public:
        const SwitchTable &GetSwitchTable() const noexcept
        {
            return switch_table_;
        }
        std::optional<SwitchSubTable> operator[](SystemSubMode mode) const noexcept
        {
            if (switch_table_.find(mode) == std::end(switch_table_))
            {
                return std::nullopt;    
            }
            return switch_table_.at(mode);
        }
        std::optional<SwitchSubTable> At(SystemSubMode mode) const noexcept
        {
            return operator[](mode);
        }
        std::optional<SwitchSubTable> GetSubSwitchTable(SystemSubMode mode) const noexcept
        {
            return operator[](mode);
        }
        std::optional<SwitchFunction> At(SystemSubMode from_mode, SystemSubMode to_mode) const noexcept
        {
            if (switch_table_.find(from_mode) == std::end(switch_table_))
            {
                return std::nullopt;
            }
            const auto & sub_table = switch_table_.at(from_mode);
            if (sub_table.find(to_mode) == std::end(sub_table))
            {
                return std::nullopt;
            }
            return sub_table.at(to_mode);
        }
        std::optional<SwitchFunction> GetSwitchFunction(SystemSubMode from_mode, SystemSubMode to_mode) const noexcept
        {
            return At(from_mode, to_mode);
        }
        void AddSwitchEntry(SystemSubMode from_mode, SystemSubMode to_mode, SwitchFunction && func)
        {
            if (switch_table_.find(from_mode) == std::end(switch_table_))
            {
                switch_table_[from_mode] = {{to_mode, std::move(func)}};
            }
            else
            {
                switch_table_[from_mode][to_mode] = std::move(func);
            }
        }
        void AddSwitchTable(SystemSubMode from_mode, SwitchSubTable && sub_table)
        {
            switch_table_[from_mode] = std::move(sub_table);
        }
        void ClearEntry(SystemSubMode from_mode, SystemSubMode to_mode)
        {
            if (switch_table_.find(from_mode) != std::end(switch_table_))
            {
                auto & sub_table = switch_table_.at(from_mode);
                if (sub_table.find(to_mode) != std::end(sub_table))
                {
                    sub_table.erase(to_mode);
                }
            }
        }
        void ClearTable(SystemSubMode from_mode)
        {
            if (switch_table_.find(from_mode) != std::end(switch_table_))
            {
                switch_table_.erase(from_mode);
            }
        }
        void Clear()
        {
            switch_table_.clear();
        }
        bool HasEntry(SystemSubMode from_mode, SystemSubMode to_mode) const noexcept
        {
            if (switch_table_.find(from_mode) != std::end(switch_table_))
            {
                const auto & sub_table = switch_table_.at(from_mode);
                return sub_table.find(to_mode) != std::end(sub_table);
            }
            return false;
        }
    };
};
