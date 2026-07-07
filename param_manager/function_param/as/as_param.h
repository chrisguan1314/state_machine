#pragma once

#include <string>
#include <type_traits>
#include <filesystem>

class AsParam
{
public:
    std::filesystem::path as_param_path_;
public:
    AsParam() = default;
    template <typename T, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<T>, std::filesystem::path>>>
    AsParam(T && path) : as_param_path_(std::forward<T>(path))
    {

    }   
};