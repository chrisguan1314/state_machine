#pragma once

#include "../../../../enum.h"
#include "apo_action.h"
#include "apo_inputer.h"
#include "apo_param.h"
#include "apo_switcher.h"
#include "../../../state_machine_outputer_base.h"

#include <iostream>

namespace parking
{
    class ApoOutputer : public StateMachineOutputer<ApoStateType>
    {
    public:
        ApoOutputer()
            : StateMachineOutputer<ApoStateType>(std::make_shared<ApoAction>()) {}

        void InitWriters() override
        {
            std::cout << "Init ApoOutputer Writers" << std::endl;
        }

        void InitActionTable() override
        {
            AddAction(ApoStateType::IDLE_0, std::bind(&ApoOutputer::ActionOfIdle, this));
            AddAction(ApoStateType::STANDBY_1, std::bind(&ApoOutputer::ActionOfStandby, this));
            AddAction(ApoStateType::PREPARING_2, std::bind(&ApoOutputer::ActionPreparing, this));
            AddAction(ApoStateType::PREPARED_3, std::bind(&ApoOutputer::ActionOfPrepared, this));
            AddAction(ApoStateType::PARKING_4, std::bind(&ApoOutputer::ActionOfParking, this));
            AddAction(ApoStateType::SUSPEND_5, std::bind(&ApoOutputer::ActionOfSuspend, this));
            AddAction(ApoStateType::OVERRIDE_6, std::bind(&ApoOutputer::ActionOfOverride, this));
            AddAction(ApoStateType::SUCCESS_7, std::bind(&ApoOutputer::ActionOfSuccess, this));
            AddAction(ApoStateType::FAILED_8, std::bind(&ApoOutputer::ActionOfFailed, this));
            AddAction(ApoStateType::TERMINATE_9, std::bind(&ApoOutputer::ActionOfTerminate, this));
        }

        ApoStateType GetCrntState() const noexcept override
        {
            return ApoStateSwitcher::GetCrntState();
        }
    private:
        void ActionOfIdle()
        {
            // std::cout << "ApoOutputer Action : IDLE" << std::endl;
        }
        void ActionOfStandby()
        {
            std::cout << "ApoOutputer Action : STANDBY" << std::endl;
        }
        void ActionPreparing()
        {
            std::cout << "ApoOutputer Action : PREPARING" << std::endl;
        }
        void ActionOfPrepared()
        {
            std::cout << "ApoOutputer Action : PREPARED" << std::endl;
        }
        void ActionOfParking()
        {
            std::cout << "ApoOutputer Action : PARKING" << std::endl;
        }
        void ActionOfSuspend()
        {
            std::cout << "ApoOutputer Action : SUSPEND" << std::endl;
        }
        void ActionOfOverride()
        {
            std::cout << "ApoOutputer Action : OVERRIDE" << std::endl;
        }
        void ActionOfSuccess()
        {
            std::cout << "ApoOutputer Action : SUCCESS" << std::endl;
        }
        void ActionOfFailed()
        {
            std::cout << "ApoOutputer Action : FAILED" << std::endl;
        }
        void ActionOfTerminate()
        {
            std::cout << "ApoOutputer Action : TERMINATE" << std::endl;
        }
    };
}