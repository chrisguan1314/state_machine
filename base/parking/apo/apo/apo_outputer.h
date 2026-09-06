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
    class ApoOutputer : public StateMachineOutputerBase<ApoStateType>
    {
    public:
        ApoOutputer()
            : StateMachineOutputerBase<ApoStateType>(std::make_shared<ApoAction>()) {}

        void InitWriters() override
        {
            std::cout << "Init ApoOutputer Writers" << std::endl;
        }

        void InitActionTable() override
        {
            AddAction(ApoStateType::IDLE_0, std::bind(&ApoOutputer::ActionIdle, this));
            AddAction(ApoStateType::STANDBY_1, std::bind(&ApoOutputer::ActionStandby, this));
            AddAction(ApoStateType::PREPARING_2, std::bind(&ApoOutputer::ActionPreparing, this));
            AddAction(ApoStateType::PREPARED_3, std::bind(&ApoOutputer::ActionPrepared, this));
            AddAction(ApoStateType::PARKING_4, std::bind(&ApoOutputer::ActionParking, this));
            AddAction(ApoStateType::SUSPEND_5, std::bind(&ApoOutputer::ActionSuspend, this));
            AddAction(ApoStateType::OVERRIDE_6, std::bind(&ApoOutputer::ActionOverride, this));
            AddAction(ApoStateType::SUCCESS_7, std::bind(&ApoOutputer::ActionSuccess, this));
            AddAction(ApoStateType::FAILED_8, std::bind(&ApoOutputer::ActionFailed, this));
            AddAction(ApoStateType::TERMINATE_9, std::bind(&ApoOutputer::ActionTerminate, this));
        }

        ApoStateType GetCrntState() const noexcept override
        {
            return ApoStateSwitcher::GetCrntState();
        }
    private:
        void ActionIdle()
        {
            // std::cout << "ApoOutputer Action : IDLE" << std::endl;
        }
        void ActionStandby()
        {
            std::cout << "ApoOutputer Action : STANDBY" << std::endl;
        }
        void ActionPreparing()
        {
            std::cout << "ApoOutputer Action : PREPARING" << std::endl;
        }
        void ActionPrepared()
        {
            std::cout << "ApoOutputer Action : PREPARED" << std::endl;
        }
        void ActionParking()
        {
            std::cout << "ApoOutputer Action : PARKING" << std::endl;
        }
        void ActionSuspend()
        {
            std::cout << "ApoOutputer Action : SUSPEND" << std::endl;
        }
        void ActionOverride()
        {
            std::cout << "ApoOutputer Action : OVERRIDE" << std::endl;
        }
        void ActionSuccess()
        {
            std::cout << "ApoOutputer Action : SUCCESS" << std::endl;
        }
        void ActionFailed()
        {
            std::cout << "ApoOutputer Action : FAILED" << std::endl;
        }
        void ActionTerminate()
        {
            std::cout << "ApoOutputer Action : TERMINATE" << std::endl;
        }
    };
}