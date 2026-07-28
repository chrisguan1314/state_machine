#pragma once

#include "../../enum.h"
#include "../../log_base.h"
#include "../../base/state_machine_printer_base.h"

#include <string>
#include <iostream>
#include <unordered_map>

class AvpCruisingPrinter : public StateMachinePrinterBase<AvpCruisingStateType>
{
private:
    const std::unordered_map<AvpCruisingStateType, std::string> avp_cruising_str_map_ = 
    {
        {AvpCruisingStateType::IDLE_0, Convert("IDLE_0")},
            {AvpCruisingStateType::STANDBY_1, Convert("STANDBY_1")},
            {AvpCruisingStateType::LOCATING_2, Convert("LOCATING_2")},
            {AvpCruisingStateType::LOCATED_3, Convert("LOCATED_3")},
            {AvpCruisingStateType::PREPARED_4, Convert("PREPARED_4")},
            {AvpCruisingStateType::CRUISING_5, Convert("CRUISING_5")},
            {AvpCruisingStateType::PARKING_6, Convert("PARKING_6")},
            {AvpCruisingStateType::OVERRIDE_7, Convert("OVERRIDE_7")},
            {AvpCruisingStateType::SUSPEND_8, Convert("SUSPEND_8")},
            {AvpCruisingStateType::TERMINATE_9, Convert("TERMINATE_9")},
            {AvpCruisingStateType::SUCCESS_10, Convert("SUCCESS_10")},
            {AvpCruisingStateType::FAILED_11, Convert("FAILED_11")},
    };
private:
    const std::string Convert(std::string&& str)
    {
        auto pos = str.find('_');
        return (pos != std::string::npos) ? (str.substr(0, pos) + "[" + str.substr(pos + 1, (str.size() - pos - 1)) + "]") : str;
    }
    const std::string AvpFormator(const std::string& str)
    {
        return Format(str, avp_cruising_str_map_);
    }
public:
    void PrintStateSwitchInfo(AvpCruisingStateType crnt_state, AvpCruisingStateType  last_state, AvpCruisingStateType prvs_state, uint32_t duration) override
    {
        std::cout << "[Avp] Crnt State : " << AvpFormator(avp_cruising_str_map_.at(crnt_state)) 
            << ", Last State : " << AvpFormator(avp_cruising_str_map_.at(last_state))
            << ", Prvs State : " << AvpFormator(avp_cruising_str_map_.at(prvs_state)) 
            << ", Duration : " << duration << "(S)" << std::endl;
    };
};