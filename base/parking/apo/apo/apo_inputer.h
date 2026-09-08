#pragma once

#include "apo_event.h"
#include "apo_param.h"
#include "../../../state_machine_inputer_base.h"

#include <iostream>

namespace parking
{
    class ApoInputer : public StateMachineInputer
    {
    public:
        void InitReaders() override
        {
            std::cout << "Init ApoInputer Readers" << std::endl;
        }

        void UpdateEvent() override {}
    };
}