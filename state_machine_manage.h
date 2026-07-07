#pragma once

#include <iostream>
#include <string>

#include "avp_cruising_state_machine.h"

class StateMachineManager
{
private:
    // 行车
    // 泊车
    bool avm_enable_flag_{false};
    bool apa_enable_flag_{false};
    bool rpa_enable_flag_{false};
    bool ra_enable_flag_{false};
    bool hpa_enable_flag_{false};
    bool avp_enable_flag_{false};
    bool park2park_enable_flag_{false};
    // 主动安全
public:
    StateMachineManager(const std::string& path)
    {
        LoadEnableParams(path);
    }
public:
    void Init()
    {
        if (avp_enable_flag_)
        {
            if (auto& avp_cruising_sm = AvpCruisingStateMachine::GetInstance())
            {
                avp_cruising_sm->Setup();
            }
            else
            {
                std::cout << "Failed to Create avp_cruising_sm object!" << std::endl;
            }
        }
        else
        {
            std::cout << "Avp enable flag : " << std::boolalpha << avp_enable_flag_ << std::endl;
        }

    }
private:
    void LoadEnableParams(const std::string& path)
    {
        avp_enable_flag_ = true;
    }
};