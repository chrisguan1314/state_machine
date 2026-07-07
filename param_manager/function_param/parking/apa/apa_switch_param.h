#pragma once

#include <string>
#include <atomic>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <type_traits>

namespace fs = std::filesystem;

struct ApaSwitchParam
{
private:
    std::filesystem::path apa_switch_param_path_;
public:
    std::atomic<bool> front_camera_switch_{true};
    std::atomic<bool> rear_camera_switch_{true};
    std::atomic<bool> left_camera_switch_{true};
    std::atomic<bool> right_camera_switch_{true};
public:
    template <typename T, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<T>, std::filesystem::path>>>
    ApaSwitchParam(T && path) : apa_switch_param_path_(std::forward<T>(path))
    {
        if (fs::exists(apa_switch_param_path_) && fs::is_regular_file(apa_switch_param_path_))
        {
            std::cout << "APA Switch Param Path :" << apa_switch_param_path_ << std::endl;
            std::ifstream ifs(apa_switch_param_path_);
            if (ifs.is_open()) 
            {
                front_camera_switch_.store(false);
                rear_camera_switch_.store(false);
                left_camera_switch_.store(false);
                right_camera_switch_.store(false);
                ifs.close();
            } 
            else 
            {
                std::cerr << "Failed to Open File : " << apa_switch_param_path_ << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid APA Switch Param Path : " << apa_switch_param_path_ << std::endl;
        }
    }
};