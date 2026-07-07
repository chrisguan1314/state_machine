#pragma once

#include "apa\apa_param.h"
#include "avm\avm_param.h"
#include "avp\avp_param.h"
#include "rpa\rpa_param.h"

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

struct ParkingParam
{
public:
    std::filesystem::path parking_param_path_;
    AvmParam avm_param_;
    ApaParam apa_param_;
    RpaParam rpa_param_;
    AvpParam avp_param_;
public:
    template <typename T, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<T>, std::filesystem::path>>>
    ParkingParam(T && path) : 
    parking_param_path_(std::forward<T>(path)),
    // avm_param_(path + "avm"),
    apa_param_(parking_param_path_/std::filesystem::path("apa"))
    // rpa_param_(path + "rpa"),
    // avp_param_(path + "avp")
    {
        if (fs::exists(parking_param_path_) && fs::is_directory(parking_param_path_))
        {
            std::cout << "Parking Param Path :" << parking_param_path_ << std::endl;
        }
        else
        {
            std::cerr << "Invalid Parking Param Path : " << parking_param_path_ << std::endl;
        }
    }
};