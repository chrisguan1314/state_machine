#pragma once

#include "avp_mapping_action.h"
#include "../../../state_machine_outputer_base.h"

#include <iostream>

namespace parking
{
class AvpMappingOutputer : public StateMachineOutputerBase<AvpMappingStateType, AvpMappingParam, AvpMappingInputer, AvpMappingStateSwitcher>
{
public:
    AvpMappingOutputer() : StateMachineOutputerBase<AvpMappingStateType, AvpMappingParam, AvpMappingInputer, AvpMappingStateSwitcher>(std::make_shared<AvpMappingAction>())
    {

    }
public:
    void InitWriters() override 
    {
        std::cout << "Init AvpMappingOutputer Writers" << std::endl;
    };
    void InitActionTable() override 
    {
        AddAction(AvpMappingStateType::IDLE_0, std::bind(&AvpMappingOutputer::ActionIdle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpMappingStateType::STANDBY_1, std::bind(&AvpMappingOutputer::ActionStandby, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpMappingStateType::ONLINE_LEARNING_2, std::bind(&AvpMappingOutputer::ActionOnlineLearning, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpMappingStateType::OFFLINE_LEARNING_3, std::bind(&AvpMappingOutputer::ActionOfflineLearning, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpMappingStateType::PARKING_4, std::bind(&AvpMappingOutputer::ActionParking, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpMappingStateType::SUCCESS_5, std::bind(&AvpMappingOutputer::ActionSuccess, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpMappingStateType::FAILED_6, std::bind(&AvpMappingOutputer::ActionFailed, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpMappingStateType::TERMINATE_7, std::bind(&AvpMappingOutputer::ActionTerminate, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    };
private:
    void ActionIdle(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input, std::shared_ptr<AvpMappingStateSwitcher> switcher)
    {
        std::cout << "AvpMappingOutputer Action : IDLE" << std::endl;
    };
    void ActionStandby(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input, std::shared_ptr<AvpMappingStateSwitcher> switcher)
    {
        std::cout << "AvpMappingOutputer Action : STANDBY" << std::endl;
    };
    void ActionOnlineLearning(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input, std::shared_ptr<AvpMappingStateSwitcher> switcher)
    {
        std::cout << "AvpMappingOutputer Action : ONLINE_LEARNING" << std::endl;
    };
    void ActionOfflineLearning(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input, std::shared_ptr<AvpMappingStateSwitcher> switcher)
    {
        std::cout << "AvpMappingOutputer Action : OFFLINE_LEARNING" << std::endl;
    };
    void ActionParking(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input, std::shared_ptr<AvpMappingStateSwitcher> switcher)
    {
        std::cout << "AvpMappingOutputer Action : PARKING" << std::endl;
    };
    void ActionSuccess(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input, std::shared_ptr<AvpMappingStateSwitcher> switcher)
    {
        std::cout << "AvpMappingOutputer Action : SUCCESS" << std::endl;
    };
    void ActionFailed(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input, std::shared_ptr<AvpMappingStateSwitcher> switcher)
    {
        std::cout << "AvpMappingOutputer Action : FAILED" << std::endl;
    };
    void ActionTerminate(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input, std::shared_ptr<AvpMappingStateSwitcher> switcher)
    {
        std::cout << "AvpMappingOutputer Action : TERMINATE" << std::endl;
    };
};
};
