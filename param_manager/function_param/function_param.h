#pragma once

#include <memory>
#include <string>
#include <filesystem>
#include <exception>

#include "pilot\pilot_param.h"
#include "parking\parking_param.h"
#include "as\as_param.h"

namespace fs = std::filesystem;

struct FunctionParam
{
private: 
    std::filesystem::path function_param_path_;
public:
    PilotParam pilot_param_;
    ParkingParam parking_param_;
    AsParam as_param_;
public: 
    template <typename T, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<T>,  fs::path>>>
    FunctionParam(T && path) : 
    function_param_path_(std::forward<T>(path)),
    pilot_param_(path/std::filesystem::path("pilot")),
    parking_param_(path/std::filesystem::path("parking")),
    as_param_(path/std::filesystem::path("as"))
    {
        if (fs::exists(function_param_path_) && fs::is_directory(function_param_path_))
        {
            std::cout << "Function Param Path :" << function_param_path_ << std::endl;
        }
        else
        {
            std::cerr << "Invalid Function Param Path : " << function_param_path_ << std::endl;
        } 
    }
};