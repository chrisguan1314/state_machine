#pragma once

#include "../../../../str_map.h"
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

    class ApoStateSwitcher : public StateMachineSwitcherBase<ApoStateType>
    {
private:
        bool SwitchFromIdleToStandby() const noexcept
        {
            return false;
        }
        bool SwitchFromStandbyToIdle() const noexcept
        {
            return false;
        }
        bool SwitchFromStandbyToPreparing() const noexcept
        {
            return false;
        }
        bool SwitchFromStandbyToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparingToPrepared() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparingToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToPreparing() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToParking() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToSuspend() const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToOverride() const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToSuccess() const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToFailed() const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromSuspendToParking() const noexcept
        {
            return false;
        }
        bool SwitchFromSuspendToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromOverrideToParking() const noexcept
        {
            return false;
        }
        bool SwitchFromOverrideToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromSuccessToStandby() const noexcept
        {
            return false;
        }
        bool SwitchFromFailedToStandby() const noexcept
        {
            return false;
        }
        bool SwitchFromTerminateToStandby() const noexcept
        {
            return false;
        }
    public:
        void Init() override
        {
            AddStateSwitch(ApoStateType::IDLE_0, {
                {ApoStateType::STANDBY_1, std::bind(&ApoStateSwitcher::SwitchFromIdleToStandby, this)}
            });
            AddStateSwitch(ApoStateType::STANDBY_1, {
                {ApoStateType::IDLE_0, std::bind(&ApoStateSwitcher::SwitchFromStandbyToIdle, this)},
                {ApoStateType::PREPARING_2, std::bind(&ApoStateSwitcher::SwitchFromStandbyToPreparing, this)}
            });
            AddStateSwitch(ApoStateType::PREPARING_2, {
                {ApoStateType::PREPARED_3, std::bind(&ApoStateSwitcher::SwitchFromPreparingToPrepared, this)},
                {ApoStateType::TERMINATE_9, std::bind(&ApoStateSwitcher::SwitchFromPreparingToTerminate, this)}
            });
            AddStateSwitch(ApoStateType::PREPARED_3, {
                {ApoStateType::PREPARING_2, std::bind(&ApoStateSwitcher::SwitchFromPreparedToPreparing, this)},
                {ApoStateType::PARKING_4, std::bind(&ApoStateSwitcher::SwitchFromPreparedToParking, this)},
                {ApoStateType::TERMINATE_9, std::bind(&ApoStateSwitcher::SwitchFromPreparedToTerminate, this)},
            });
            AddStateSwitch(ApoStateType::PARKING_4, {
                {ApoStateType::SUSPEND_5, std::bind(&ApoStateSwitcher::SwitchFromParkingToSuspend, this)},
                {ApoStateType::OVERRIDE_6, std::bind(&ApoStateSwitcher::SwitchFromParkingToOverride, this)},
                {ApoStateType::SUCCESS_7, std::bind(&ApoStateSwitcher::SwitchFromParkingToSuccess, this)},
                {ApoStateType::FAILED_8, std::bind(&ApoStateSwitcher::SwitchFromParkingToFailed, this)},
                {ApoStateType::TERMINATE_9, std::bind(&ApoStateSwitcher::SwitchFromParkingToTerminate, this)}
            });
            AddStateSwitch(ApoStateType::SUSPEND_5, {
                {ApoStateType::PARKING_4, std::bind(&ApoStateSwitcher::SwitchFromSuspendToParking, this)},
                {ApoStateType::TERMINATE_9, std::bind(&ApoStateSwitcher::SwitchFromSuspendToTerminate, this)}
            });
            AddStateSwitch(ApoStateType::OVERRIDE_6, {
                {ApoStateType::PARKING_4, std::bind(&ApoStateSwitcher::SwitchFromOverrideToParking, this)},
                {ApoStateType::TERMINATE_9, std::bind(&ApoStateSwitcher::SwitchFromOverrideToTerminate, this)},
            });
            AddStateSwitch(ApoStateType::SUCCESS_7,  {
                {ApoStateType::STANDBY_1, std::bind(&ApoStateSwitcher::SwitchFromSuccessToStandby, this)},
            });
            AddStateSwitch(ApoStateType::FAILED_8, {
                {ApoStateType::STANDBY_1, std::bind(&ApoStateSwitcher::SwitchFromFailedToStandby, this)},
            });
            AddStateSwitch(ApoStateType::TERMINATE_9, {
                {ApoStateType::STANDBY_1, std::bind(&ApoStateSwitcher::SwitchFromTerminateToStandby, this)},
            });
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