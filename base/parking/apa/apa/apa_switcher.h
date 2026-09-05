#pragma once

#include "../../../../str_map.h"
#include "apa_inputer.h"
#include "apa_param.h"
#include "../../../state_machine_switcher_base.h"
#include "../../../state_switch_table.h"

#include <iostream>

namespace parking
{
    inline std::string ApaFormator(const std::string &value)
    {
        return Format(value, apa_str_map);
    }

    class ApaStateSwitcher : public StateMachineSwitcherBase<ApaStateType, ApaParam, ApaInputer>
    {
    private:
        StateSwitchTable<ApaStateType, ApaParam, ApaInputer> table_;

    public:
        ApaStateSwitcher() : StateMachineSwitcherBase<ApaStateType, ApaParam, ApaInputer>() {}

    private:
        bool SwitchFromIdleToStandby(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromStandbyToIdle(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) noexcept
        {
            return false;
        }
        bool SwitchFromStandbyToSearching(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromSearchingToSearched(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromSearchingToTerminate(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromSearchedToSearching(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromSearchedToPrepared(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromSearchedToTerminate(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToSearching(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToRpaPrepared(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            if (param->IsRpaEnable())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromPreparedToParking(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToTerminate(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromRpaPreparedToPrepared(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromRpaPreparedToParking(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromRpaPreparedToTerminate(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToSuspend(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToOverride(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToSuccess(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToFailed(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToTerminate(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromSuspendToParking(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromSuspendToTerminate(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromOverrideToParking(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }   
        bool SwitchFromOverrideToTerminate(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromSuccessToStandby(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromFailedToStandby(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
        bool SwitchFromTerminateToStandby(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) const noexcept
        {
            return false;
        }
    public:
        void Init() override
        {
            using SwitchSubTable = StateSwitchTable<ApaStateType, ApaParam, ApaInputer>::SwitchSubTable;

            SwitchSubTable idle_to_table =
            {
                {ApaStateType::STANDBY_1, std::bind(&ApaStateSwitcher::SwitchFromIdleToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            };
            SwitchSubTable standby_to_table =
            {
                {ApaStateType::IDLE_0, std::bind(&ApaStateSwitcher::SwitchFromStandbyToIdle, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::SEARCHING_2, std::bind(&ApaStateSwitcher::SwitchFromStandbyToSearching, this, std::placeholders::_1, std::placeholders::_2)},
            };
            SwitchSubTable searching_to_table =
            {
                {ApaStateType::SEARCHED_3, std::bind(&ApaStateSwitcher::SwitchFromSearchingToSearched, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromSearchingToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
            };
            SwitchSubTable searched_to_table =
            {
                {ApaStateType::SEARCHING_2, std::bind(&ApaStateSwitcher::SwitchFromSearchedToSearching, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::PREPARED_4, std::bind(&ApaStateSwitcher::SwitchFromSearchedToPrepared, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromSearchedToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
            };
            SwitchSubTable prepared_to_table =
            {
                {ApaStateType::SEARCHING_2, std::bind(&ApaStateSwitcher::SwitchFromPreparedToSearching, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::RPA_PREPARED_5, std::bind(&ApaStateSwitcher::SwitchFromPreparedToRpaPrepared, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::PARKING_6, std::bind(&ApaStateSwitcher::SwitchFromPreparedToParking, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromPreparedToTerminate, this, std::placeholders::_1, std::placeholders::_2)}
            };
            SwitchSubTable rpa_prepared_to_table =
            {
                {ApaStateType::PREPARED_4, std::bind(&ApaStateSwitcher::SwitchFromRpaPreparedToPrepared, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::PARKING_6, std::bind(&ApaStateSwitcher::SwitchFromRpaPreparedToParking, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromRpaPreparedToTerminate, this, std::placeholders::_1, std::placeholders::_2)}
            };
            SwitchSubTable parking_to_table =
            {
                {ApaStateType::SUSPEND_7, std::bind(&ApaStateSwitcher::SwitchFromParkingToSuspend, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::OVERRIDE_8, std::bind(&ApaStateSwitcher::SwitchFromParkingToOverride, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::SUCCESS_9, std::bind(&ApaStateSwitcher::SwitchFromParkingToSuccess, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::FAILED_10, std::bind(&ApaStateSwitcher::SwitchFromParkingToFailed, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromParkingToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
            };
            SwitchSubTable suspend_to_table =
            {
                {ApaStateType::PARKING_6, std::bind(&ApaStateSwitcher::SwitchFromSuspendToParking, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromSuspendToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
            };
            SwitchSubTable override_to_table =
            {
                {ApaStateType::PARKING_6, std::bind(&ApaStateSwitcher::SwitchFromOverrideToParking, this, std::placeholders::_1, std::placeholders::_2)},
                {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromOverrideToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
            };
            SwitchSubTable success_to_table =
            {
                {ApaStateType::STANDBY_1, std::bind(&ApaStateSwitcher::SwitchFromSuccessToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            };
            SwitchSubTable failed_to_table =
            {
                {ApaStateType::STANDBY_1, std::bind(&ApaStateSwitcher::SwitchFromFailedToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            };
            SwitchSubTable terminate_to_table =
            {
                {ApaStateType::STANDBY_1, std::bind(&ApaStateSwitcher::SwitchFromTerminateToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            };

            table_.AddStateSwitch(ApaStateType::IDLE_0, std::move(idle_to_table));
            table_.AddStateSwitch(ApaStateType::STANDBY_1, std::move(standby_to_table));
            table_.AddStateSwitch(ApaStateType::SEARCHING_2, std::move(searching_to_table));
            table_.AddStateSwitch(ApaStateType::SEARCHED_3, std::move(searched_to_table));
            table_.AddStateSwitch(ApaStateType::PREPARED_4, std::move(prepared_to_table));
            table_.AddStateSwitch(ApaStateType::RPA_PREPARED_5, std::move(rpa_prepared_to_table));
            table_.AddStateSwitch(ApaStateType::PARKING_6, std::move(parking_to_table));
            table_.AddStateSwitch(ApaStateType::SUSPEND_7, std::move(suspend_to_table));
            table_.AddStateSwitch(ApaStateType::OVERRIDE_8, std::move(override_to_table));
            table_.AddStateSwitch(ApaStateType::SUCCESS_9, std::move(success_to_table));
            table_.AddStateSwitch(ApaStateType::FAILED_10, std::move(failed_to_table));
            table_.AddStateSwitch(ApaStateType::TERMINATE_11, std::move(terminate_to_table));

            std::cout << "[StateMachine] Init Switcher Table" << std::endl;
        }

        ApaStateType CalcNextState(std::shared_ptr<ApaParam> param, std::shared_ptr<ApaInputer> input) override
        {
            auto crnt_state = GetCrntState();
            const auto& state_switch_list = table_.GetStateSwitchTable(crnt_state);
            for (const auto& [to_state, switch_function] : state_switch_list)
            {
                if (switch_function(param, input))
                {
                    crnt_state = to_state;
                    break;
                }
            }
            return crnt_state;
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