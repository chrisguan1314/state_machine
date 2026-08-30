#pragma once

#include <string>
#include <filesystem>
#include <stdexcept>
#include <iostream>

struct PilotEnbleParam
{
    bool acc_enable_{false};
    bool lcc_enable_{false};
};

struct ParkingEnableParam
{
    bool apa_enable_{false};
    bool apo_enable_{false};
    bool avm_enable_{false};
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
    ~SystemParam() = default;

    SystemParam(const SystemParam &) = delete;
    SystemParam &operator=(const SystemParam &) = delete;
    SystemParam(SystemParam &&) = delete;
    SystemParam &operator=(SystemParam &&) = delete;

    void LoadParameters(const std::string &parameter_file_path)
    {
        if (!std::filesystem::exists(parameter_file_path))
        {
            // throw std::runtime_error("Parameter file not found: " + parameter_file_path);
            parking_enable_param_.avp_cruising_enable_ = true;

            // Print all feature enable states
            PrintParameters();
        }
        else
        {
            // Load parameters from the file
            // For example, you can use a JSON library to parse the file and set the parameters accordingly
            parking_enable_param_.avp_cruising_enable_ = true;

            // Print all feature enable states
            PrintParameters();
        }
    }
private:
    void PrintParameters() const
    {
        std::cout << "AVP Cruising Enable: " << std::boolalpha << parking_enable_param_.avp_cruising_enable_ << std::endl;
    }
public:
    const PilotEnbleParam &GetPilotEnableParam() const noexcept
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
    PilotEnbleParam pilot_enable_param_{false};
    ParkingEnableParam parking_enable_param_{false};
    ActiveSafetyEnableParam active_safety_enable_param_{false};
};