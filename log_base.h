#pragma once

#include "base/concept_base.h"

#include <map>
#include <string>
#include <algorithm>
#include <type_traits>

#if __cplusplus >= 202002L
template <is_enum T>
#else
template <typename T, typename = typename std::enable_if_t<std::is_enum_v<T>>>
#endif
using StateStrMap = std::map<T, std::string>;

#if __cplusplus >= 202002L
template <is_enum T>
#else
template <typename T, typename = typename std::enable_if_t<std::is_enum_v<T>>>
#endif
const std::string Format(const std::string& str, const StateStrMap<T>& str_map)
{
    uint32_t max_size = 0;
    std::for_each(std::begin(str_map), std::end(str_map), [&max_size](auto item){
        if (item.second.size() > max_size)
        {
            max_size = item.second.size();
        }
    });
    const uint32_t size = str.size();
    return (size < max_size) ? std::string(max_size - size + 1, ' ') : std::string(" ");
}