#pragma once

#include "avp_cruising_value_param.h"
#include "avp_cruising_switch_param.h"

class AvpCruisingParam
{
private: 
    // 每一个类都对应一个json参数文件
    AvpCruisingSwitchParam switch_param_;
    AvpCruisingValueParam value_param_;
public:
    const AvpCruisingSwitchParam& GetSwitchParam() const noexcept
    {
        return switch_param_;
    }
    const AvpCruisingValueParam& GetValueParam() const noexcept
    {
        return value_param_;
    }
    AvpCruisingSwitchParam& GetSwitchParam() noexcept 
    {
        return switch_param_;
    }
    AvpCruisingValueParam& GetValueParam() noexcept
    {
        return value_param_;
    }
    void SetSwitchParam(AvpCruisingSwitchParam && param)
    {
        switch_param_ = std::move(param);
    }
    void SetValueParam(AvpCruisingValueParam && param)
    {
        value_param_ = std::move(param);
    }
};