#pragma once

#include "../../../state_machine_param_base.h"

#include <iostream>

namespace parking
{
class ApaParam : public StateMachineParamBase
{
public:
    void Init() override
    {
        std::cout << "[StateMachine] Init ApaParam" << std::endl;
    }

    void UpdateParam() override {}
private:
    bool rpa_enable_{false};
public:
    bool IsRpaEnable() const noexcept
    {
        return rpa_enable_;
    }
    void SetRpaEnable(bool enable) noexcept
    {
        rpa_enable_ = enable;
    }
};
}