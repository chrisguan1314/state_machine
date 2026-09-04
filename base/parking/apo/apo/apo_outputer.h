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
    class ApoOutputer : public StateMachineOutputerBase<ApoStateType, ApoParam, ApoInputer, ApoStateSwitcher>
    {
    public:
        ApoOutputer()
            : StateMachineOutputerBase<ApoStateType, ApoParam, ApoInputer, ApoStateSwitcher>(std::make_shared<ApoAction>()) {}

        void InitWriters() override
        {
            std::cout << "Init ApoOutputer Writers" << std::endl;
        }

        void InitActionTable() override
        {
            AddAction(ApoStateType::IDLE_0, std::bind(&ApoOutputer::ActionIdle, this,
                                                      std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            AddAction(ApoStateType::STANDBY_1, std::bind(&ApoOutputer::ActionStandby, this,
                                                         std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            AddAction(ApoStateType::PREPARING_2, std::bind(&ApoOutputer::ActionPreparing, this,
                                                           std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            AddAction(ApoStateType::PREPARED_3, std::bind(&ApoOutputer::ActionPrepared, this,
                                                          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            AddAction(ApoStateType::PARKING_4, std::bind(&ApoOutputer::ActionParking, this,
                                                         std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            AddAction(ApoStateType::SUSPEND_5, std::bind(&ApoOutputer::ActionSuspend, this,
                                                         std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            AddAction(ApoStateType::OVERRIDE_6, std::bind(&ApoOutputer::ActionOverride, this,
                                                          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            AddAction(ApoStateType::SUCCESS_7, std::bind(&ApoOutputer::ActionSuccess, this,
                                                         std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            AddAction(ApoStateType::FAILED_8, std::bind(&ApoOutputer::ActionFailed, this,
                                                        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            AddAction(ApoStateType::TERMINATE_9, std::bind(&ApoOutputer::ActionTerminate, this,
                                                           std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        }

    private:
        void ActionIdle(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>, std::shared_ptr<ApoStateSwitcher>)
        {
            // std::cout << "ApoOutputer Action : IDLE" << std::endl;
        }
        void ActionStandby(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>, std::shared_ptr<ApoStateSwitcher>)
        {
            std::cout << "ApoOutputer Action : STANDBY" << std::endl;
        }
        void ActionPreparing(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>, std::shared_ptr<ApoStateSwitcher>)
        {
            std::cout << "ApoOutputer Action : PREPARING" << std::endl;
        }
        void ActionPrepared(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>, std::shared_ptr<ApoStateSwitcher>)
        {
            std::cout << "ApoOutputer Action : PREPARED" << std::endl;
        }
        void ActionParking(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>, std::shared_ptr<ApoStateSwitcher>)
        {
            std::cout << "ApoOutputer Action : PARKING" << std::endl;
        }
        void ActionSuspend(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>, std::shared_ptr<ApoStateSwitcher>)
        {
            std::cout << "ApoOutputer Action : SUSPEND" << std::endl;
        }
        void ActionOverride(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>, std::shared_ptr<ApoStateSwitcher>)
        {
            std::cout << "ApoOutputer Action : OVERRIDE" << std::endl;
        }
        void ActionSuccess(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>, std::shared_ptr<ApoStateSwitcher>)
        {
            std::cout << "ApoOutputer Action : SUCCESS" << std::endl;
        }
        void ActionFailed(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>, std::shared_ptr<ApoStateSwitcher>)
        {
            std::cout << "ApoOutputer Action : FAILED" << std::endl;
        }
        void ActionTerminate(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>, std::shared_ptr<ApoStateSwitcher>)
        {
            std::cout << "ApoOutputer Action : TERMINATE" << std::endl;
        }
    };
}