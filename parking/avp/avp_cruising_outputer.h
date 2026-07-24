#pragma once

#include "avp_cruising_action.h"
#include "../../base/state_machine_outputer_base.h"

#include <iostream>

namespace parking
{
class AvpCruisingOutputer : public StateMachineOutputerBase<AvpCruisingStateType, AvpCruisingParam, AvpCruisingInputer, AvpCruisingStateSwitcher>
{
public:
    AvpCruisingOutputer() : StateMachineOutputerBase<AvpCruisingStateType, AvpCruisingParam, AvpCruisingInputer, AvpCruisingStateSwitcher>(std::make_shared<AvpCruisingAction>())
    {

    }
public:
    void InitWriters() override 
    {
        std::cout << "Init AvpCruisingOutputer Writers" << std::endl;
    };
    void InitActionTable() override 
    {
        AddAction(AvpCruisingStateType::IDLE_0, std::bind(&AvpCruisingOutputer::ActionIdle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingOutputer::ActionStandby, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingOutputer::ActionLocating, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpCruisingStateType::LOCATED_3, std::bind(&AvpCruisingOutputer::ActionLocated, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpCruisingStateType::PREPARED_4, std::bind(&AvpCruisingOutputer::ActionPrepared, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingOutputer::ActionCruising, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpCruisingStateType::PARKING_6, std::bind(&AvpCruisingOutputer::ActionParking, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpCruisingStateType::OVERRIDE_7, std::bind(&AvpCruisingOutputer::ActionOverride, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpCruisingStateType::SUCCESS_10, std::bind(&AvpCruisingOutputer::ActionSuccess, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpCruisingStateType::FAILED_11, std::bind(&AvpCruisingOutputer::ActionFailed, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpCruisingStateType::SUSPEND_8, std::bind(&AvpCruisingOutputer::ActionSuspend, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(AvpCruisingStateType::TERMINATE_9, std::bind(&AvpCruisingOutputer::ActionTerminate, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    };
private:
    void ActionIdle(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher)
    {
        // std::cout << "AvpCruisingOutputer Action : IDLE" << std::endl;
    };
    void ActionStandby(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher)
    {
        // std::cout << "AvpCruisingOutputer Action : STANDBY" << std::endl;
    };
    void ActionLocating(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher)
    {
        std::cout << "AvpCruisingOutputer Action : LOCATING" << std::endl;
    };
    void ActionLocated(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher)
    {
        std::cout << "AvpCruisingOutputer Action : LOCATED" << std::endl;
    };
    void ActionPrepared(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher)
    {
        std::cout << "AvpCruisingOutputer Action : PREPARED" << std::endl;
    };
    void ActionCruising(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher)
    {
        std::cout << "AvpCruisingOutputer Action : CRUISING" << std::endl;
    };
    void ActionParking(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher)
    {
        std::cout << "AvpCruisingOutputer Action : PARKING" << std::endl;
    };
    void ActionOverride(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher)
    {
        std::cout << "AvpCruisingOutputer Action : OVERRIDE" << std::endl;
    };
    void ActionSuccess(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher)
    {
        std::cout << "AvpCruisingOutputer Action : SUCCESS" << std::endl;
    };
    void ActionFailed(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher)
    {
        std::cout << "AvpCruisingOutputer Action : FAILED" << std::endl;
    };
    void ActionSuspend(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher)
    {
        std::cout << "AvpCruisingOutputer Action : SUSPEND" << std::endl;
    };
    void ActionTerminate(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher)
    {
        std::cout << "AvpCruisingOutputer Action : TERMINATE" << std::endl;
    };
};
};
