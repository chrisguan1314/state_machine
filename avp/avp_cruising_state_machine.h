#pragma once

#include "../enum.h"
#include "../str_map.h"
#include "../log_base.h"
#include "../state_machine_base.h"
#include "avp_cruising_param.h"
#include "avp_cruising_input.h"
#include "avp_cruising_switch.h"
#include "avp_cruising_output.h"

namespace avp_cruising
{
const std::string AvpFormator(const std::string& str)
{
    return Format(str, avp_cruising_str_map);
}
class AvpCruisingStateMachine : public StateMachineBase<AvpCruisingStateType>
{
public:
    static std::unique_ptr<AvpCruisingStateMachine>& GetInstance()
    {
        static std::unique_ptr<AvpCruisingStateMachine> avp_sm_uptr_(new AvpCruisingStateMachine);
        return avp_sm_uptr_;
    }
private: 
    AvpCruisingStateMachine() :  
    StateMachineBase<AvpCruisingStateType>("AvpCruising", std::make_shared<AvpCruisingParam>(), std::make_shared<AvpCruisingInput>(), std::make_shared<AvpCruisingStateSwitch>(), std::make_shared<AvpCruisingOutput>())
    {
        
    }
    void PrintStateSwitchInfo() override 
    {
        std::cout << "[Avp] Crnt State : " << AvpFormator(avp_cruising_str_map.at(GetCrntState())) 
                << ", Last State : " << AvpFormator(avp_cruising_str_map.at(GetLastState()))
                << ", Prvs State : " << AvpFormator(avp_cruising_str_map.at(GetPrvsState())) 
                << ", Duration : " << GetDuration().count() << "(S)" << std::endl; 
    };
    AvpCruisingStateType CalcNextState() const noexcept override
    { 
        std::cout << "222" << std::endl;
        return AvpCruisingStateType::IDLE_0; 
    };
};
};
