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
        std::cout << "Init ApaParam" << std::endl;
    }

    void UpdateParam() override {}
};
}