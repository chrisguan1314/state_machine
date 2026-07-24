#pragma once

#include "enum.h"
#include "log_base.h"

const std::string Convert(std::string&& str)
{
    auto pos = str.find('_');
    return (pos != std::string::npos) ? (str.substr(0, pos) + "[" + str.substr(pos + 1, (str.size() - pos - 1)) + "]") : str;
}

// 可以统一抽象出一个Convert函数，这样想要修改输出字符串格式的时候就不用一个一个修改了
str_unordered_map<AvpCruisingStateType> avp_cruising_str_map = 
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