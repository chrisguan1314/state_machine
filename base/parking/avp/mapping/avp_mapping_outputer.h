#pragma once

#include "avp_mapping_action.h"
#include "../../../state_machine_outputer_base.h"

#include <iostream>

namespace parking
{
class AvpMappingOutputer : public StateMachineOutputerBase<AvpMappingStateType>
{
public:
    AvpMappingOutputer() : StateMachineOutputerBase<AvpMappingStateType>(std::make_shared<AvpMappingAction>())
    {

    }
public:
    void InitWriters() override 
    {
        std::cout << "Init AvpMappingOutputer Writers" << std::endl;
    };
    void InitActionTable() override 
    {
        AddAction(AvpMappingStateType::IDLE_0, std::bind(&AvpMappingOutputer::ActionIdle, this));
        AddAction(AvpMappingStateType::STANDBY_1, std::bind(&AvpMappingOutputer::ActionStandby, this));
        AddAction(AvpMappingStateType::ONLINE_LEARNING_2, std::bind(&AvpMappingOutputer::ActionOnlineLearning, this));
        AddAction(AvpMappingStateType::OFFLINE_LEARNING_3, std::bind(&AvpMappingOutputer::ActionOfflineLearning, this));
        AddAction(AvpMappingStateType::PARKING_4, std::bind(&AvpMappingOutputer::ActionParking, this));
        AddAction(AvpMappingStateType::SUCCESS_5, std::bind(&AvpMappingOutputer::ActionSuccess, this));
        AddAction(AvpMappingStateType::FAILED_6, std::bind(&AvpMappingOutputer::ActionFailed, this));
        AddAction(AvpMappingStateType::TERMINATE_7, std::bind(&AvpMappingOutputer::ActionTerminate, this));
    };

    AvpMappingStateType GetCrntState() const noexcept override
    {
        return AvpMappingStateSwitcher::GetCrntState();
    }
private:
    void ActionIdle()
    {
        // std::cout << "AvpMappingOutputer Action : IDLE" << std::endl;
    };
    void ActionStandby()
    {
        // std::cout << "AvpMappingOutputer Action : STANDBY" << std::endl;
    };
    void ActionOnlineLearning()
    {
        // std::cout << "AvpMappingOutputer Action : ONLINE_LEARNING" << std::endl;
    };
    void ActionOfflineLearning()
    {
        // std::cout << "AvpMappingOutputer Action : OFFLINE_LEARNING" << std::endl;
    };
    void ActionParking()
    {
        // std::cout << "AvpMappingOutputer Action : PARKING" << std::endl;
    };
    void ActionSuccess()
    {
        // std::cout << "AvpMappingOutputer Action : SUCCESS" << std::endl;
    };
    void ActionFailed()
    {
        // std::cout << "AvpMappingOutputer Action : FAILED" << std::endl;
    };
    void ActionTerminate()
    {
        // std::cout << "AvpMappingOutputer Action : TERMINATE" << std::endl;
    };
};
};
