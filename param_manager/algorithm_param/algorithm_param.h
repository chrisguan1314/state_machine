#pragma once

#include <filesystem>

class AlgorithmParam
{
private: 
    std::filesystem::path algorithm_param_path_;
public:
    template <typename T, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<T>,  std::filesystem::path>>>
    AlgorithmParam(T && path) : algorithm_param_path_(path)
    {

    }
};