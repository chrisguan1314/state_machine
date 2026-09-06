#pragma once

#include "../../../../enum.h"
#include "apa_action.h"
#include "apa_switcher.h"
#include "../../../state_machine_outputer_base.h"

#include <iostream>

namespace parking
{
    class ApaOutputer : public StateMachineOutputerBase<ApaStateType>
    {
    public:
        ApaOutputer() : StateMachineOutputerBase<ApaStateType>(std::make_shared<ApaAction>()) {}

        void InitWriters() override
        {
            std::cout << "[StateMachine] Init ApaOutputer Writers" << std::endl;
        }

        void InitActionTable() override
        {
            AddAction(ApaStateType::IDLE_0, std::bind(&ApaOutputer::ActionIdle, this));
            AddAction(ApaStateType::STANDBY_1, std::bind(&ApaOutputer::ActionStandby, this));
            AddAction(ApaStateType::SEARCHING_2, std::bind(&ApaOutputer::ActionSearching, this));
            AddAction(ApaStateType::SEARCHED_3, std::bind(&ApaOutputer::ActionSearched, this));
            AddAction(ApaStateType::PREPARED_4, std::bind(&ApaOutputer::ActionPrepared, this));
            AddAction(ApaStateType::RPA_PREPARED_5, std::bind(&ApaOutputer::ActionRpaPrepared, this));
            AddAction(ApaStateType::PARKING_6, std::bind(&ApaOutputer::ActionParking, this));
            AddAction(ApaStateType::SUSPEND_7, std::bind(&ApaOutputer::ActionSuspend, this));
            AddAction(ApaStateType::OVERRIDE_8, std::bind(&ApaOutputer::ActionOverride, this));
            AddAction(ApaStateType::SUCCESS_9, std::bind(&ApaOutputer::ActionSuccess, this));
            AddAction(ApaStateType::FAILED_10, std::bind(&ApaOutputer::ActionFailed, this));
            AddAction(ApaStateType::TERMINATE_11, std::bind(&ApaOutputer::ActionTerminate, this));
        }

        ApaStateType GetCrntState() const noexcept override
        {
            return ApaStateSwitcher::GetCrntState();
        }
    private:
        void ActionIdle() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::IDLE_0))
            {
                std::cout << "ApaOutputer Action : IDLE" << std::endl; 
            }
        }
        void ActionStandby() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::STANDBY_1))
            {
                ApaStateSwitcher::SetOpenType(FuncOpenType::NONE_0);
                ApaStateSwitcher::SetActvType(FuncActvType::NONE_0);
                std::cout << "ApaOutputer Action : STANDBY" << std::endl; 
            }
        }
        void ActionSearching() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::SEARCHING_2))
            {
                ApaStateSwitcher::SetOpenType(FuncOpenType::TICE_1);
                std::cout << "ApaOutputer Action : SEARCHING" << std::endl; 
            }
        }
        void ActionSearched() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::SEARCHED_3))
            {
                std::cout << "ApaOutputer Action : SEARCHED" << std::endl; 
            }
        }
        void ActionPrepared() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::PREPARED_4))
            {
                std::cout << "ApaOutputer Action : PREPARED" << std::endl; 
            }
        }
        void ActionRpaPrepared() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::RPA_PREPARED_5))
            {
                std::cout << "ApaOutputer Action : RPA_PREPARED" << std::endl; 
            }
        }
        void ActionParking() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::PARKING_6))
            {
                if (ApaStateSwitcher::IsChangeFrom(ApaStateType::PREPARED_4))
                {
                    ApaStateSwitcher::SetActvType(FuncActvType::TICE_1);
                    std::cout << "ApaOutputer Action : PARKING" << std::endl; 
                }
                else if (ApaStateSwitcher::IsChangeFrom(ApaStateType::RPA_PREPARED_5))
                {
                    ApaStateSwitcher::SetActvType(FuncActvType::KEY_5);
                    std::cout << "ApaOutputer Action : PARKING" << std::endl; 
                }
            }
        }
        void ActionSuspend() 
        { 
            std::cout << "ApaOutputer Action : SUSPEND" << std::endl; 
        }
        void ActionOverride() 
        { 
            std::cout << "ApaOutputer Action : OVERRIDE" << std::endl; 
        }
        void ActionSuccess()
        { 
            std::cout << "ApaOutputer Action : SUCCESS" << std::endl; 
        }
        void ActionFailed() 
        { 
            std::cout << "ApaOutputer Action : FAILED" << std::endl; 
        }
        void ActionTerminate() 
        { 
            std::cout << "ApaOutputer Action : TERMINATE" << std::endl; 
        }
    };
}