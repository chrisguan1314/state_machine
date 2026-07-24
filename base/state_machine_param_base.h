#pragma once

class StateMachineParamBase
{
public:
    virtual void Init() = 0; 
    virtual void UpdateParam() = 0;
};

#if __cplusplus >= 202002L
template <typename T>
concept is_param_base = std::derived_from<T, StateMachineParamBase>;
#endif