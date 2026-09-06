#pragma once

#include "enum.h"
#include "log_base.h"

template <typename T, typename = typename std::enable_if_t<std::is_enum_v<T>>>
using str_unordered_map = std::unordered_map<T, std::string>;

const std::string Convert(std::string&& str)
{
    auto pos = str.find('_');
    return (pos != std::string::npos) ? (str.substr(0, pos) + "[" + str.substr(pos + 1, (str.size() - pos - 1)) + "]") : str;
}

str_unordered_map<ApaStateType> apa_str_map =
{
    {ApaStateType::IDLE_0, Convert("IDLE_0")},
    {ApaStateType::STANDBY_1, Convert("STANDBY_1")},
    {ApaStateType::SEARCHING_2, Convert("SEARCHING_2")},
    {ApaStateType::SEARCHED_3, Convert("SEARCHED_3")},
    {ApaStateType::PREPARED_4, Convert("PREPARED_4")},
    {ApaStateType::RPA_PREPARED_5, Convert("RPA_PREPARED_5")},
    {ApaStateType::PARKING_6, Convert("PARKING_6")},
    {ApaStateType::SUSPEND_7, Convert("SUSPEND_7")},
    {ApaStateType::OVERRIDE_8, Convert("OVERRIDE_8")},
    {ApaStateType::SUCCESS_9, Convert("SUCCESS_9")},
    {ApaStateType::FAILED_10, Convert("FAILED_10")},
    {ApaStateType::TERMINATE_11, Convert("TERMINATE_11")},
};

str_unordered_map<ApoStateType> apo_str_map =
{
    {ApoStateType::IDLE_0, Convert("IDLE_0")},
    {ApoStateType::STANDBY_1, Convert("STANDBY_1")},
    {ApoStateType::PREPARING_2, Convert("PREPARING_2")},
    {ApoStateType::PREPARED_3, Convert("PREPARED_3")},
    {ApoStateType::PARKING_4, Convert("PARKING_4")},
    {ApoStateType::SUSPEND_5, Convert("SUSPEND_5")},
    {ApoStateType::OVERRIDE_6, Convert("OVERRIDE_6")},
    {ApoStateType::SUCCESS_7, Convert("SUCCESS_7")},
    {ApoStateType::FAILED_8, Convert("FAILED_8")},
    {ApoStateType::TERMINATE_9, Convert("TERMINATE_9")},
};

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
    {AvpCruisingStateType::SUCCESS_8, Convert("SUCCESS_8")},
    {AvpCruisingStateType::FAILED_9, Convert("FAILED_9")},
    {AvpCruisingStateType::SUSPEND_10, Convert("SUSPEND_10")},
    {AvpCruisingStateType::TERMINATE_11, Convert("TERMINATE_11")},
};

str_unordered_map<AvpMappingStateType> avp_mapping_str_map =
{
    {AvpMappingStateType::IDLE_0, Convert("IDLE_0")},
    {AvpMappingStateType::STANDBY_1, Convert("STANDBY_1")},
    {AvpMappingStateType::ONLINE_LEARNING_2, Convert("ONLINE_LEARNING_2")},
    {AvpMappingStateType::OFFLINE_LEARNING_3, Convert("OFFLINE_LEARNING_3")},
    {AvpMappingStateType::PARKING_4, Convert("PARKING_4")},
    {AvpMappingStateType::SUCCESS_5, Convert("SUCCESS_5")},
    {AvpMappingStateType::FAILED_6, Convert("FAILED_6")},
    {AvpMappingStateType::TERMINATE_7, Convert("TERMINATE_7")},
};