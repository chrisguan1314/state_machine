#pragma once

#include "apa_switch_param.h"
#include "apa_value_param.h"

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

struct ApaParam
{
public:
    std::filesystem::path apa_param_path_;
    ApaSwitchParam switch_param_;
    ApaValueParam value_param_;
public:
    template <typename T, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<T>, std::filesystem::path>>>
    ApaParam(T && path) : 
    apa_param_path_(std::forward<T>(path)),
    switch_param_(apa_param_path_/std::filesystem::path("switch_param.json")),
    value_param_(apa_param_path_/std::filesystem::path("value_param.json"))
    {
        if (fs::exists(apa_param_path_) && fs::is_directory(apa_param_path_))
        {
            std::cout << "APA Param Path :" << apa_param_path_ << std::endl;
        }
        else
        {
            std::cerr << "Invalid APA Param Path : " << apa_param_path_ << std::endl;
        }
    }
};