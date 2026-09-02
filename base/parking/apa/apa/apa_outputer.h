#pragma once

#include "../../../../enum.h"
#include "apa_action.h"
#include "apa_inputer.h"
#include "apa_param.h"
#include "apa_switcher.h"
#include "../../../state_machine_outputer_base.h"

#include <iostream>

namespace parking
{
class ApaOutputer : public StateMachineOutputerBase<ApaStateType, ApaParam, ApaInputer, ApaStateSwitcher>
{
public:
    ApaOutputer() : StateMachineOutputerBase<ApaStateType, ApaParam, ApaInputer, ApaStateSwitcher>(std::make_shared<ApaAction>()) {}

    void InitWriters() override
    {
        std::cout << "Init ApaOutputer Writers" << std::endl;
    }

    void InitActionTable() override
    {
        AddAction(ApaStateType::IDLE_0, std::bind(&ApaOutputer::ActionIdle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(ApaStateType::STANDBY_1, std::bind(&ApaOutputer::ActionStandby, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(ApaStateType::SEARCHING_2, std::bind(&ApaOutputer::ActionSearching, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(ApaStateType::SEARCHED_3, std::bind(&ApaOutputer::ActionSearched, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(ApaStateType::PREPARED_4, std::bind(&ApaOutputer::ActionPrepared, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(ApaStateType::RPA_PREPARED_5, std::bind(&ApaOutputer::ActionRpaPrepared, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(ApaStateType::PARKING_6, std::bind(&ApaOutputer::ActionParking, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(ApaStateType::SUSPEND_7, std::bind(&ApaOutputer::ActionSuspend, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(ApaStateType::OVERRIDE_8, std::bind(&ApaOutputer::ActionOverride, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(ApaStateType::SUCCESS_9, std::bind(&ApaOutputer::ActionSuccess, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(ApaStateType::FAILED_10, std::bind(&ApaOutputer::ActionFailed, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        AddAction(ApaStateType::TERMINATE_11, std::bind(&ApaOutputer::ActionTerminate, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

private:
    void ActionIdle(std::shared_ptr<ApaParam>, std::shared_ptr<ApaInputer>, std::shared_ptr<ApaStateSwitcher>) { std::cout << "ApaOutputer Action : IDLE" << std::endl; }
    void ActionStandby(std::shared_ptr<ApaParam>, std::shared_ptr<ApaInputer>, std::shared_ptr<ApaStateSwitcher>) { std::cout << "ApaOutputer Action : STANDBY" << std::endl; }
    void ActionSearching(std::shared_ptr<ApaParam>, std::shared_ptr<ApaInputer>, std::shared_ptr<ApaStateSwitcher>) { std::cout << "ApaOutputer Action : SEARCHING" << std::endl; }
    void ActionSearched(std::shared_ptr<ApaParam>, std::shared_ptr<ApaInputer>, std::shared_ptr<ApaStateSwitcher>) { std::cout << "ApaOutputer Action : SEARCHED" << std::endl; }
    void ActionPrepared(std::shared_ptr<ApaParam>, std::shared_ptr<ApaInputer>, std::shared_ptr<ApaStateSwitcher>) { std::cout << "ApaOutputer Action : PREPARED" << std::endl; }
    void ActionRpaPrepared(std::shared_ptr<ApaParam>, std::shared_ptr<ApaInputer>, std::shared_ptr<ApaStateSwitcher>) { std::cout << "ApaOutputer Action : RPA_PREPARED" << std::endl; }
    void ActionParking(std::shared_ptr<ApaParam>, std::shared_ptr<ApaInputer>, std::shared_ptr<ApaStateSwitcher>) { std::cout << "ApaOutputer Action : PARKING" << std::endl; }
    void ActionSuspend(std::shared_ptr<ApaParam>, std::shared_ptr<ApaInputer>, std::shared_ptr<ApaStateSwitcher>) { std::cout << "ApaOutputer Action : SUSPEND" << std::endl; }
    void ActionOverride(std::shared_ptr<ApaParam>, std::shared_ptr<ApaInputer>, std::shared_ptr<ApaStateSwitcher>) { std::cout << "ApaOutputer Action : OVERRIDE" << std::endl; }
    void ActionSuccess(std::shared_ptr<ApaParam>, std::shared_ptr<ApaInputer>, std::shared_ptr<ApaStateSwitcher>) { std::cout << "ApaOutputer Action : SUCCESS" << std::endl; }
    void ActionFailed(std::shared_ptr<ApaParam>, std::shared_ptr<ApaInputer>, std::shared_ptr<ApaStateSwitcher>) { std::cout << "ApaOutputer Action : FAILED" << std::endl; }
    void ActionTerminate(std::shared_ptr<ApaParam>, std::shared_ptr<ApaInputer>, std::shared_ptr<ApaStateSwitcher>) { std::cout << "ApaOutputer Action : TERMINATE" << std::endl; }
};
}