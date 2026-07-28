#pragma once

template <typename T>
class StateMachinePrinterBase
{
public:
    virtual void PrintStateSwitchInfo(T crnt_state, T last_state, T prvs_state, uint32_t duration) = 0;
};