#pragma once

#include "../../../../str_map.h"
#include "apo_inputer.h"
#include "apo_param.h"
#include "../../../state_machine_switcher_base.h"
#include "../../../state_switch_table.h"
#include "../.././../base.h"

#include <iostream>

namespace parking
{
    inline std::string ApoFormator(const std::string &value)
    {
        return Format(value, apo_str_map);
    }

    class ApoStateSwitcher : public StateMachineSwitcherBase<ApoStateType, ApoParam, ApoInputer>
    {
    private:
        StateSwitchTable<ApoStateType, ApoParam, ApoInputer> table_;

        bool SwitchFromIdleToStandby(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromStandbyToIdle(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromStandbyToPreparing(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromStandbyToTerminate(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromPreparingToPrepared(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromPreparingToTerminate(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToPreparing(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToParking(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToTerminate(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToSuspend(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToOverride(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToSuccess(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToFailed(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToTerminate(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromSuspendToParking(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromSuspendToTerminate(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromOverrideToParking(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromOverrideToTerminate(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromSuccessToStandby(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromFailedToStandby(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
        bool SwitchFromTerminateToStandby(std::shared_ptr<ApoParam>, std::shared_ptr<ApoInputer>) const noexcept
        {
            return false;
        }
    public:
        void Init() override
        {
            table_.AddStateSwitch(ApoStateType::IDLE_0, {
                {ApoStateType::STANDBY_1, std::bind(&ApoStateSwitcher::SwitchFromIdleToStandby, this, std::placeholders::_1, std::placeholders::_2)}
            });
            table_.AddStateSwitch(ApoStateType::STANDBY_1, {
                {ApoStateType::IDLE_0, std::bind(&ApoStateSwitcher::SwitchFromStandbyToIdle, this, std::placeholders::_1, std::placeholders::_2)},
                {ApoStateType::PREPARING_2, std::bind(&ApoStateSwitcher::SwitchFromStandbyToPreparing, this, std::placeholders::_1, std::placeholders::_2)}
            });
            table_.AddStateSwitch(ApoStateType::PREPARING_2, {
                {ApoStateType::PREPARED_3, std::bind(&ApoStateSwitcher::SwitchFromPreparingToPrepared, this, std::placeholders::_1, std::placeholders::_2)},
                {ApoStateType::TERMINATE_9, std::bind(&ApoStateSwitcher::SwitchFromPreparingToTerminate, this, std::placeholders::_1, std::placeholders::_2)}
            });
            table_.AddStateSwitch(ApoStateType::PREPARED_3, {
                {ApoStateType::PREPARING_2, std::bind(&ApoStateSwitcher::SwitchFromPreparedToPreparing, this, std::placeholders::_1, std::placeholders::_2)},
                {ApoStateType::PARKING_4, std::bind(&ApoStateSwitcher::SwitchFromPreparedToParking, this, std::placeholders::_1, std::placeholders::_2)},
                {ApoStateType::TERMINATE_9, std::bind(&ApoStateSwitcher::SwitchFromPreparedToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
            });
            table_.AddStateSwitch(ApoStateType::PARKING_4, {
                {ApoStateType::SUSPEND_5, std::bind(&ApoStateSwitcher::SwitchFromParkingToSuspend, this, std::placeholders::_1, std::placeholders::_2)},
                {ApoStateType::OVERRIDE_6, std::bind(&ApoStateSwitcher::SwitchFromParkingToOverride, this, std::placeholders::_1, std::placeholders::_2)},
                {ApoStateType::SUCCESS_7, std::bind(&ApoStateSwitcher::SwitchFromParkingToSuccess, this, std::placeholders::_1, std::placeholders::_2)},
                {ApoStateType::FAILED_8, std::bind(&ApoStateSwitcher::SwitchFromParkingToFailed, this, std::placeholders::_1, std::placeholders::_2)},
                {ApoStateType::TERMINATE_9, std::bind(&ApoStateSwitcher::SwitchFromParkingToTerminate, this, std::placeholders::_1, std::placeholders::_2)}
            });
            table_.AddStateSwitch(ApoStateType::SUSPEND_5, {
                {ApoStateType::PARKING_4, std::bind(&ApoStateSwitcher::SwitchFromSuspendToParking, this, std::placeholders::_1, std::placeholders::_2)},
                {ApoStateType::TERMINATE_9, std::bind(&ApoStateSwitcher::SwitchFromSuspendToTerminate, this, std::placeholders::_1, std::placeholders::_2)}
            });
            table_.AddStateSwitch(ApoStateType::OVERRIDE_6, {
                {ApoStateType::PARKING_4, std::bind(&ApoStateSwitcher::SwitchFromOverrideToParking, this, std::placeholders::_1, std::placeholders::_2)},
                {ApoStateType::TERMINATE_9, std::bind(&ApoStateSwitcher::SwitchFromOverrideToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
            });
            table_.AddStateSwitch(ApoStateType::SUCCESS_7,  {
                {ApoStateType::STANDBY_1, std::bind(&ApoStateSwitcher::SwitchFromSuccessToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            });
            table_.AddStateSwitch(ApoStateType::FAILED_8, {
                {ApoStateType::STANDBY_1, std::bind(&ApoStateSwitcher::SwitchFromFailedToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            });
            table_.AddStateSwitch(ApoStateType::TERMINATE_9, {
                {ApoStateType::STANDBY_1, std::bind(&ApoStateSwitcher::SwitchFromTerminateToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            });
        }

        ApoStateType CalcNextState(std::shared_ptr<ApoParam> param,
                                   std::shared_ptr<ApoInputer> input) override
        {
            const auto current_state = GetCrntState();
            const auto &transitions = table_.GetStateSwitchTable(current_state);
            for (const auto &[next_state, switch_func] : transitions)
            {
                if (switch_func(param, input))
                {
                    return next_state;
                }
            }
            return current_state;
        }

        static bool IsRunning() noexcept
        {
            return GetCrntState() > ApoStateType::STANDBY_1;
        }

        void PrintStateSwitchInfo() override
        {
            std::cout << "[APO] Crnt : " << ApoFormator(apo_str_map.at(GetCrntState()))
                      << ", Last : " << ApoFormator(apo_str_map.at(GetLastState()))
                      << ", Prvs : " << ApoFormator(apo_str_map.at(GetPrvsState()))
                      << ", Duration : " << GetDuration().count() << "(S)" << std::endl;
        }
    };
}