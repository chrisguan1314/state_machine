#pragma once

#include "../../../../str_map.h"
#include "../../../state_machine_switcher_base.h"
#include "../../../state_switch_table.h"

#include <iostream>

namespace parking
{
    inline std::string ApaFormator(const std::string &value)
    {
        return Format(value, apa_str_map);
    }

    class ApaStateSwitcher : public StateMachineSwitcherBase<ApaStateType>
    {
    public:
        ApaStateSwitcher() : StateMachineSwitcherBase<ApaStateType>() {}

    private:
        bool SwitchFromIdleToStandby() const noexcept
        {
            return false;
        }
        bool SwitchFromStandbyToIdle() noexcept
        {
            return false;
        }
        bool SwitchFromStandbyToSearching() const noexcept
        {
            return false;
        }
        bool SwitchFromSearchingToSearched() const noexcept
        {
            return false;
        }
        bool SwitchFromSearchingToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromSearchedToSearching() const noexcept
        {
            return false;
        }
        bool SwitchFromSearchedToPrepared() const noexcept
        {
            return false;
        }
        bool SwitchFromSearchedToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToSearching() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToRpaPrepared() const noexcept
        {
            if (ApaParam::IsRpaEnable())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromPreparedToParking() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromRpaPreparedToPrepared() const noexcept
        {
            return false;
        }
        bool SwitchFromRpaPreparedToParking() const noexcept
        {
            return false;
        }
        bool SwitchFromRpaPreparedToTerminate() const noexcept
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
            using SwitchSubTable = StateSwitchTable<ApaStateType>::SwitchSubTable;

            SwitchSubTable idle_to_table =
            {
                {ApaStateType::STANDBY_1, std::bind(&ApaStateSwitcher::SwitchFromIdleToStandby, this)},
            };
            SwitchSubTable standby_to_table =
            {
                {ApaStateType::IDLE_0, std::bind(&ApaStateSwitcher::SwitchFromStandbyToIdle, this)},
                {ApaStateType::SEARCHING_2, std::bind(&ApaStateSwitcher::SwitchFromStandbyToSearching, this)},
            };
            SwitchSubTable searching_to_table =
            {
                {ApaStateType::SEARCHED_3, std::bind(&ApaStateSwitcher::SwitchFromSearchingToSearched, this)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromSearchingToTerminate, this)},
            };
            SwitchSubTable searched_to_table =
            {
                {ApaStateType::SEARCHING_2, std::bind(&ApaStateSwitcher::SwitchFromSearchedToSearching, this)},
                {ApaStateType::PREPARED_4, std::bind(&ApaStateSwitcher::SwitchFromSearchedToPrepared, this)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromSearchedToTerminate, this)},
            };
            SwitchSubTable prepared_to_table =
            {
                {ApaStateType::SEARCHING_2, std::bind(&ApaStateSwitcher::SwitchFromPreparedToSearching, this)},
                {ApaStateType::RPA_PREPARED_5, std::bind(&ApaStateSwitcher::SwitchFromPreparedToRpaPrepared, this)},
                {ApaStateType::PARKING_6, std::bind(&ApaStateSwitcher::SwitchFromPreparedToParking, this)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromPreparedToTerminate, this)}
            };
            SwitchSubTable rpa_prepared_to_table =
            {
                {ApaStateType::PREPARED_4, std::bind(&ApaStateSwitcher::SwitchFromRpaPreparedToPrepared, this)},
                {ApaStateType::PARKING_6, std::bind(&ApaStateSwitcher::SwitchFromRpaPreparedToParking, this)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromRpaPreparedToTerminate, this)}
            };
            SwitchSubTable parking_to_table =
            {
                {ApaStateType::SUSPEND_7, std::bind(&ApaStateSwitcher::SwitchFromParkingToSuspend, this)},
                {ApaStateType::OVERRIDE_8, std::bind(&ApaStateSwitcher::SwitchFromParkingToOverride, this)},
                {ApaStateType::SUCCESS_9, std::bind(&ApaStateSwitcher::SwitchFromParkingToSuccess, this)},
                {ApaStateType::FAILED_10, std::bind(&ApaStateSwitcher::SwitchFromParkingToFailed, this)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromParkingToTerminate, this)},
            };
            SwitchSubTable suspend_to_table =
            {
                {ApaStateType::PARKING_6, std::bind(&ApaStateSwitcher::SwitchFromSuspendToParking, this)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromSuspendToTerminate, this)},
            };
            SwitchSubTable override_to_table =
            {
                {ApaStateType::PARKING_6, std::bind(&ApaStateSwitcher::SwitchFromOverrideToParking, this)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromOverrideToTerminate, this)},
            };
            SwitchSubTable success_to_table =
            {
                {ApaStateType::STANDBY_1, std::bind(&ApaStateSwitcher::SwitchFromSuccessToStandby, this)},
            };
            SwitchSubTable failed_to_table =
            {
                {ApaStateType::STANDBY_1, std::bind(&ApaStateSwitcher::SwitchFromFailedToStandby, this)},
            };
            SwitchSubTable terminate_to_table =
            {
                {ApaStateType::STANDBY_1, std::bind(&ApaStateSwitcher::SwitchFromTerminateToStandby, this)},
            };

            GetSwtichTable().AddStateSwitch(ApaStateType::IDLE_0, std::move(idle_to_table));
            GetSwtichTable().AddStateSwitch(ApaStateType::STANDBY_1, std::move(standby_to_table));
            GetSwtichTable().AddStateSwitch(ApaStateType::SEARCHING_2, std::move(searching_to_table));
            GetSwtichTable().AddStateSwitch(ApaStateType::SEARCHED_3, std::move(searched_to_table));
            GetSwtichTable().AddStateSwitch(ApaStateType::PREPARED_4, std::move(prepared_to_table));
            GetSwtichTable().AddStateSwitch(ApaStateType::RPA_PREPARED_5, std::move(rpa_prepared_to_table));
            GetSwtichTable().AddStateSwitch(ApaStateType::PARKING_6, std::move(parking_to_table));
            GetSwtichTable().AddStateSwitch(ApaStateType::SUSPEND_7, std::move(suspend_to_table));
            GetSwtichTable().AddStateSwitch(ApaStateType::OVERRIDE_8, std::move(override_to_table));
            GetSwtichTable().AddStateSwitch(ApaStateType::SUCCESS_9, std::move(success_to_table));
            GetSwtichTable().AddStateSwitch(ApaStateType::FAILED_10, std::move(failed_to_table));
            GetSwtichTable().AddStateSwitch(ApaStateType::TERMINATE_11, std::move(terminate_to_table));

            std::cout << "[StateMachine] Init Switcher Table" << std::endl;
        }

        static bool IsRunning() noexcept
        {
            return GetCrntState() > ApaStateType::STANDBY_1;
        }

        void PrintStateSwitchInfo() override
        {
            std::cout << "[APA] Crnt : " << ApaFormator(apa_str_map.at(GetCrntState()))
                      << ", Last : " << ApaFormator(apa_str_map.at(GetLastState()))
                      << ", Prvs : " << ApaFormator(apa_str_map.at(GetPrvsState()))
                      << ", Duration : " << GetDuration().count() << "(S)" << std::endl;
        }
    };
}