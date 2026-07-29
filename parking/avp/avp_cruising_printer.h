#pragma once

#include "../../enum.h"
#include "../../log_base.h"
#include "../../base/state_machine_printer_base.h"

#include <string>
#include <iostream>
#include <functional>

class AvpCruisingPrinter : public StateMachinePrinterBase<AvpCruisingStateType>
{
private:
    using AvpCruisingFormator = std::function<const std::string(const std::string&)>;
private:
    const StateStrMap<AvpCruisingStateType> avp_cruising_str_map_ = 
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
        {AvpCruisingStateType::FAILED_11, Convert("FAILED_11")}
    };
    AvpCruisingFormator formator_ = [this](const std::string& str) { return Format(str, avp_cruising_str_map_); };
public:
    void PrintStateSwitchInfo(AvpCruisingStateType crnt_state, AvpCruisingStateType  last_state, AvpCruisingStateType prvs_state, uint32_t duration) override
    {
        const std::string crnt_state_str = avp_cruising_str_map_.at(crnt_state);
        const std::string last_state_str = avp_cruising_str_map_.at(last_state);
        const std::string prvs_state_str = avp_cruising_str_map_.at(prvs_state);
        std::cout << "[Avp Cruising] Crnt State : " << crnt_state_str << ", " << formator_(crnt_state_str)
            << "Last State : " << last_state_str << ", " << formator_(last_state_str)
            << "Prvs State : " << prvs_state_str << ", " << formator_(prvs_state_str)
            << "Duration : " << duration << "(S)" << std::endl;
    };
};