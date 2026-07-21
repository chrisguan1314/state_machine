#pragma once

#include "avp_cruising_action.h"
#include "../base/state_machine_outputer_base.h"

#include <memory>
#include <iostream>

namespace parking
{
class AvpCruisingOutputer : public StateMachineOutputerBase
{
public:
    AvpCruisingOutputer() : StateMachineOutputerBase(std::make_shared<AvpCruisingAction>())
    {

    }
public:
    void InitWriters() override 
    {
        std::cout << "Init AvpCruisingOutputer Writers" << std::endl;
    };
    void UpdateAction() override 
    {
        std::cout << "Update AvpCruisingOutputer Action" << std::endl;
    };
};
};
