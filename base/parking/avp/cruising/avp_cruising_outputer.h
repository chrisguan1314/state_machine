#pragma once

#include "avp_cruising_action.h"
#include "../../../state_machine_outputer_base.h"

#include <iostream>

namespace parking
{
class AvpCruisingOutputer : public StateMachineOutputer<AvpCruisingStateType>
{
public:
    AvpCruisingOutputer() : StateMachineOutputer<AvpCruisingStateType>(std::make_shared<AvpCruisingAction>())
    {

    }
public:
    void InitWriters() override 
    {
        std::cout << "Init AvpCruisingOutputer Writers" << std::endl;
    };
    void InitActionTable() override 
    {
        AddAction(AvpCruisingStateType::IDLE_0, std::bind(&AvpCruisingOutputer::ActionIdle, this));
        AddAction(AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingOutputer::ActionStandby, this));
        AddAction(AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingOutputer::ActionLocating, this));
        AddAction(AvpCruisingStateType::LOCATED_3, std::bind(&AvpCruisingOutputer::ActionLocated, this));
        AddAction(AvpCruisingStateType::PREPARED_4, std::bind(&AvpCruisingOutputer::ActionPrepared, this));
        AddAction(AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingOutputer::ActionCruising, this));
        AddAction(AvpCruisingStateType::PARKING_6, std::bind(&AvpCruisingOutputer::ActionParking, this));
        AddAction(AvpCruisingStateType::OVERRIDE_7, std::bind(&AvpCruisingOutputer::ActionOverride, this));
        AddAction(AvpCruisingStateType::SUCCESS_8, std::bind(&AvpCruisingOutputer::ActionSuccess, this));
        AddAction(AvpCruisingStateType::FAILED_9, std::bind(&AvpCruisingOutputer::ActionFailed, this));
        AddAction(AvpCruisingStateType::SUSPEND_10, std::bind(&AvpCruisingOutputer::ActionSuspend, this));
        AddAction(AvpCruisingStateType::TERMINATE_11, std::bind(&AvpCruisingOutputer::ActionTerminate, this));
    };

    AvpCruisingStateType GetCrntState() const noexcept override
    {
        return AvpCruisingStateSwitcher::GetCrntState();
    }
private:
    void ActionIdle()
    {
        // std::cout << "AvpCruisingOutputer Action : IDLE" << std::endl;
    };
    void ActionStandby()
    {
        // std::cout << "AvpCruisingOutputer Action : STANDBY" << std::endl;
    };
    void ActionLocating()
    {
        // std::cout << "AvpCruisingOutputer Action : LOCATING" << std::endl;
    };
    void ActionLocated()
    {
        // std::cout << "AvpCruisingOutputer Action : LOCATED" << std::endl;
    };
    void ActionPrepared()
    {
        // std::cout << "AvpCruisingOutputer Action : PREPARED" << std::endl;
    };
    void ActionCruising()
    {
        // std::cout << "AvpCruisingOutputer Action : CRUISING" << std::endl;
    };
    void ActionParking()
    {
        // std::cout << "AvpCruisingOutputer Action : PARKING" << std::endl;
    };
    void ActionOverride()
    {
        // std::cout << "AvpCruisingOutputer Action : OVERRIDE" << std::endl;
    };
    void ActionSuccess()
    {
        // std::cout << "AvpCruisingOutputer Action : SUCCESS" << std::endl;
    };
    void ActionFailed()
    {
        // std::cout << "AvpCruisingOutputer Action : FAILED" << std::endl;
    };
    void ActionSuspend()
    {
        // std::cout << "AvpCruisingOutputer Action : SUSPEND" << std::endl;
    };
    void ActionTerminate()
    {
        // std::cout << "AvpCruisingOutputer Action : TERMINATE" << std::endl;
    };
};
};
