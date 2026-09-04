#pragma once

#include "../../../state_machine_param_base.h"

#include <iostream>

namespace parking
{
    class ApoParam : public StateMachineParamBase
    {
    public:
        void Init() override
        {
            std::cout << "Init ApoParam" << std::endl;
        }

        void UpdateParam() override {}
    };
}