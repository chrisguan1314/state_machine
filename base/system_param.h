#pragma once

#include <string>
#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <fstream>

struct PilotEnableParam
{
    bool acc_enable_{false};
    bool lcc_enable_{false};
};

struct ParkingEnableParam
{
    bool apa_enable_{false};
    bool rpa_enable_{false};
    bool onekey_attach_{false};
    bool apo_enable_{false};
    bool rpo_enable_{false};
    bool straight_summon_{false};
    bool gesture_summon_{false};
    bool avm_enable_{false};
    bool ra_enable_{false};
    bool avp_mapping_enable_{false};
    bool avp_cruising_enable_{false};
};

struct ActiveSafetyEnableParam
{
    bool aeb_enable_{false};
    bool aes_enable_{false};
    bool meb_enable_{false};
    bool bsd_enable_{false};
};

class SystemParam
{   
public:
    SystemParam() = default;
    template <typename T, typename = typename std::enable_if_t<std::is_convertible_v<T, std::string>>>
    explicit SystemParam(T && path) : param_path_(std::forward<T>(path))
    {
        LoadParameters();
    }
    ~SystemParam() = default;

    SystemParam(const SystemParam &) = delete;
    SystemParam &operator=(const SystemParam &) = delete;
    SystemParam(SystemParam &&) = delete;
    SystemParam &operator=(SystemParam &&) = delete;

    void LoadParameters()
    {
        if (!std::filesystem::exists(param_path_) || !std::filesystem::is_regular_file(param_path_))
        {
            // throw std::runtime_error("Parameter file not found: " + parameter_file_path);
            parking_enable_param_.apa_enable_ = true;
            parking_enable_param_.avp_cruising_enable_ = true;
            parking_enable_param_.avp_mapping_enable_ = true;

            // Print all feature enable states
            PrintParameters();

            std::cerr << "[SystemScheduler][Param] Parameter file not found or invalid: " << param_path_ << std::endl;
        }
        else
        {
            std::ifstream parameter_file(param_path_);
            // Load parameters from the file
            // For example, you can use a JSON library to parse the file and set the parameters accordingly
            parking_enable_param_.apa_enable_ = true;
            parking_enable_param_.avp_cruising_enable_ = true;
            parking_enable_param_.avp_mapping_enable_ = true;

            // Print all feature enable states
            PrintParameters();
        }
    }
private:
    void PrintPilotParams() const noexcept
    {
        std::cout << "[SystemScheduler][Param][Pilot] ACC Enable: " << std::boolalpha << pilot_enable_param_.acc_enable_ << std::endl;
        std::cout << "[SystemScheduler][Param][Pilot] LCC Enable: " << std::boolalpha << pilot_enable_param_.lcc_enable_ << std::endl;
    }
    void PrintParkingParams() const noexcept
    {
        std::cout << "[SystemScheduler][Param][Parking] APA Enable: " << std::boolalpha << parking_enable_param_.apa_enable_ << std::endl;
        std::cout << "[SystemScheduler][Param][Parking] AVP Cruising Enable: " << std::boolalpha << parking_enable_param_.avp_cruising_enable_ << std::endl;
        std::cout << "[SystemScheduler][Param][Parking] AVP Mapping Enable: " << std::boolalpha << parking_enable_param_.avp_mapping_enable_ << std::endl;
    }
    void PrintAsParams() const noexcept
    {
        std::cout << "[SystemScheduler][Param][AS] AEB Enable: " << std::boolalpha << active_safety_enable_param_.aeb_enable_ << std::endl;
        std::cout << "[SystemScheduler][Param][AS] AES Enable: " << std::boolalpha << active_safety_enable_param_.aes_enable_ << std::endl;
        std::cout << "[SystemScheduler][Param][AS] MEB Enable: " << std::boolalpha << active_safety_enable_param_.meb_enable_ << std::endl;
        std::cout << "[SystemScheduler][Param][AS] BSD Enable: " << std::boolalpha << active_safety_enable_param_.bsd_enable_ << std::endl;
    }
    void PrintParameters() const
    {
        std::cout << "\n***************************************\n" << std::endl;
        PrintPilotParams();
        std::cout << "\n-------------\n" << std::endl;
        PrintParkingParams();
        std::cout << "\n-------------\n" << std::endl;
        PrintAsParams();
        std::cout << "\n***************************************\n" << std::endl;
    }
public:
    const PilotEnableParam &GetPilotEnableParam() const noexcept
    {
        return pilot_enable_param_;
    }
    const ParkingEnableParam &GetParkingEnableParam() const noexcept
    {
        return parking_enable_param_;
    }
    const ActiveSafetyEnableParam &GetActiveSafetyEnableParam() const noexcept
    {
        return active_safety_enable_param_;
    }
private:
    std::filesystem::path param_path_{};
    PilotEnableParam pilot_enable_param_{};
    ParkingEnableParam parking_enable_param_{};
    ActiveSafetyEnableParam active_safety_enable_param_{};
};