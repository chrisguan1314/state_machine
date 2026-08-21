#pragma once

#include "../../../state_machine_param_base.h"

#include <iostream>

namespace parking
{
class AvpCruisingParam : public StateMachineParamBase
{
private:
    
public:
    AvpCruisingParam() : StateMachineParamBase()
    {

    }
public:
    virtual void Init() override 
    {
        std::cout << "Init AvpCruisingParam" << std::endl;
    }; 
    virtual void UpdateParam() override {};
};
};
