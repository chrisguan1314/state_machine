#pragma once

class StateMachineParamBase
{
public:
    virtual void Init() = 0; 
    virtual void UpdateParam() = 0;
};