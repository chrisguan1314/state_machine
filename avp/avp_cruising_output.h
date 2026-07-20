#pragma once

#include "avp_cruising_action.h"
#include "../state_machine_output_base.h"

#include <memory>
#include <iostream>

namespace avp_cruising
{
class AvpCruisingOutput : public StateMachineOutputBase
{
public:
    AvpCruisingOutput() : StateMachineOutputBase(std::make_shared<AvpCruisingAction>())
    {

    }
public:
    virtual void InitWriters() override 
    {
        std::cout << "Init AvpCruisingOutput Writers" << std::endl;
    };
    virtual void UpdateAction() override 
    {
        std::cout << "Update AvpCruisingOutput Action" << std::endl;
    };
};
};
