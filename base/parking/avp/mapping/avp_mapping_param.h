#pragma once

#include "../../../state_machine_param_base.h"

#include <iostream>

namespace parking
{
class AvpMappingParam : public StateMachineParamBase
{
private:
    
public:
    AvpMappingParam() : StateMachineParamBase()
    {

    }
public:
    virtual void Init() override 
    {
        std::cout << "Init AvpMappingParam" << std::endl;
    }; 
    virtual void UpdateParam() override {};
};
};
