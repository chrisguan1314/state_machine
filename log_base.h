#pragma once

#include <unordered_map>
#include <type_traits>
#include <string>

template <typename T, typename = typename std::enable_if_t<std::is_enum_v<T>>>
using str_unordered_map = std::unordered_map<T, std::string>;

template<typename T>
const std::string Format(const std::string& str, const str_unordered_map<T>& str_map)
{
    uint32_t max_size = 0;
    for (auto it = std::begin(str_map); it != std::end(str_map); it++)
    {
        if (it->second.size() > max_size)
        {
            max_size = it->second.size();
        }
    }
    const uint32_t size = str.size();
    if (size < max_size)
    {
        std::string tmp = str;
        tmp.insert(size, (max_size - size), ' ');
        return tmp;
    }
    else
    {
        return str;
    }
}