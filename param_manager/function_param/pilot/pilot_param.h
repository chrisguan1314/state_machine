#pragma once

#include <string>
#include <utility>
#include <filesystem>
#include <type_traits>

struct PilotParam
{
public:
    std::filesystem::path pilot_param_path_;
public:
    PilotParam() = default;
    template <typename T, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<T>, std::filesystem::path>>>
    PilotParam(T && path) : pilot_param_path_(std::forward<T>(path))
    {

    }
};