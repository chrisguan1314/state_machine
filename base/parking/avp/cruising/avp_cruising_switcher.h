#pragma once

#include "../../../state_machine_switcher_base.h"
#include "../../../state_switch_table.h"
#include "../../../../log_base.h"

namespace parking
{
    const uint8_t seconds = 3;
    const std::string AvpCruisingFormator(const std::string &str)
    {
        return Format(str, avp_cruising_str_map);
    }
    class AvpCruisingStateSwitcher : public StateMachineSwitcherBase<AvpCruisingStateType>
    {
    public:
        AvpCruisingStateSwitcher() : StateMachineSwitcherBase<AvpCruisingStateType>()
        {
        }

    private:
        // *******************************SwitchFromIdle*******************************
        bool SwitchFromIdleToStandby() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // *******************************SwitchFromStandby*******************************
        bool SwitchFromStandbyToIdle() const noexcept
        {
            return false;
        }
        bool SwitchFromStandbyToLocating() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // *******************************SwitchFromLocating*******************************
        bool SwitchFromLocatingToStandby() const noexcept
        {
            return false;
        }
        bool SwitchFromLocatingToLocated() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // *******************************SwitchFromLocated*******************************
        bool SwitchFromLocatedToStandby() const noexcept
        {
            return false;
        }
        bool SwitchFromLocatedToLocating() const noexcept
        {
            return false;
        }
        bool SwitchFromLocatedToPrepared() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // *******************************SwitchFromPrepared*******************************
        bool SwitchFromPreparedToStandby() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToLocating() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToLocated() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToCruising() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // *******************************SwitchFromCruising*******************************
        bool SwitchFromCruisingToStandby() const noexcept
        {
            return false;
        }
        bool SwitchFromCruisingToParking() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromCruisingToOverride() const noexcept
        {
            return false;
        }
        bool SwitchFromCruisingToSuccess() const noexcept
        {
            return false;
        }
        bool SwitchFromCruisingToFailed() const noexcept
        {
            return false;
        }
        bool SwitchFromCruisingToSuspend() const noexcept
        {
            return false;
        }
        bool SwitchFromCruisingToTerminate() const noexcept
        {
            return false;
        }
        // *******************************SwitchFromParking*******************************
        bool SwitchFromParkingToStandby() const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToSuccess() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromParkingToFailed() const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToSuspend() const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToTerminate() const noexcept
        {
            return false;
        }
        // *******************************SwitchFromOverride*******************************
        bool SwitchFromOverrideToStandby() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromOverrideToCruising() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // *******************************SwitchFromSuccess*******************************
        bool SwitchFromSuccessToStandby() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // *******************************SwitchFromFailed*******************************
        bool SwitchFromFailedToStandby() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // *******************************SwitchFromSuspend*******************************
        bool SwitchFromSuspenedToStandby() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromSuspenedToCruising() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromSuspenedToParking() const noexcept
        {
            if (GetCount() > seconds * 20)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromSuspenedToTerminate() const noexcept
        {
            if (GetCount() > (seconds * 20 * 30))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // *******************************SwitchFromgTerminate*******************************
        bool SwitchFromTerminateToStandby() const noexcept
        {
            if (GetCount() > (seconds * 20 * 3))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

    public:
        void Init() override
        {
            using SwitchSubTable = StateSwitchTable<AvpCruisingStateType>::SwitchSubTable;

            SwitchSubTable idle_to_table =
                {
                    {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromIdleToStandby, this)},
                };

            SwitchSubTable standby_to_table =
                {
                    {AvpCruisingStateType::IDLE_0, std::bind(&AvpCruisingStateSwitcher::SwitchFromStandbyToIdle, this)},
                    {AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingStateSwitcher::SwitchFromStandbyToLocating, this)},
                };

            SwitchSubTable locating_to_table =
                {
                    {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromLocatingToStandby, this)},
                    {AvpCruisingStateType::LOCATED_3, std::bind(&AvpCruisingStateSwitcher::SwitchFromLocatingToLocated, this)},
                };

            SwitchSubTable located_to_table =
                {
                    {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromLocatedToStandby, this)},
                    {AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingStateSwitcher::SwitchFromLocatedToLocating, this)},
                    {AvpCruisingStateType::PREPARED_4, std::bind(&AvpCruisingStateSwitcher::SwitchFromLocatedToPrepared, this)},
                };

            SwitchSubTable prepared_to_table =
                {
                    {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromPreparedToStandby, this)},
                    {AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingStateSwitcher::SwitchFromPreparedToLocating, this)},
                    {AvpCruisingStateType::LOCATED_3, std::bind(&AvpCruisingStateSwitcher::SwitchFromPreparedToLocated, this)},
                    {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateSwitcher::SwitchFromPreparedToCruising, this)},
                };

            SwitchSubTable cruising_to_table =
                {
                    {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToStandby, this)},
                    {AvpCruisingStateType::PARKING_6, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToParking, this)},
                    {AvpCruisingStateType::OVERRIDE_7, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToOverride, this)},
                    {AvpCruisingStateType::SUCCESS_8, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToSuccess, this)},
                    {AvpCruisingStateType::FAILED_9, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToFailed, this)},
                    {AvpCruisingStateType::SUSPEND_10, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToSuspend, this)},
                    {AvpCruisingStateType::TERMINATE_11, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToTerminate, this)},
                };

            SwitchSubTable parking_to_table =
                {
                    {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromParkingToStandby, this)},
                    {AvpCruisingStateType::SUCCESS_8, std::bind(&AvpCruisingStateSwitcher::SwitchFromParkingToSuccess, this)},
                    {AvpCruisingStateType::FAILED_9, std::bind(&AvpCruisingStateSwitcher::SwitchFromParkingToFailed, this)},
                    {AvpCruisingStateType::SUSPEND_10, std::bind(&AvpCruisingStateSwitcher::SwitchFromParkingToSuspend, this)},
                    {AvpCruisingStateType::TERMINATE_11, std::bind(&AvpCruisingStateSwitcher::SwitchFromParkingToTerminate, this)},
                };

            SwitchSubTable override_to_table =
                {
                    {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateSwitcher::SwitchFromOverrideToStandby, this)},
                    {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateSwitcher::SwitchFromOverrideToCruising, this)},
                };

            SwitchSubTable success_to_table =
                {
                    {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromSuccessToStandby, this)},
                };

            SwitchSubTable failed_to_table =
                {
                    {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromFailedToStandby, this)},
                };

            SwitchSubTable suspend_to_table =
                {
                    {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromSuspenedToStandby, this)},
                    {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateSwitcher::SwitchFromSuspenedToCruising, this)},
                    {AvpCruisingStateType::PARKING_6, std::bind(&AvpCruisingStateSwitcher::SwitchFromSuspenedToParking, this)},
                    {AvpCruisingStateType::TERMINATE_11, std::bind(&AvpCruisingStateSwitcher::SwitchFromSuspenedToTerminate, this)},
                };

            SwitchSubTable terminate_to_table =
                {
                    {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromTerminateToStandby, this)},
                };

            GetSwtichTable().AddStateSwitch(AvpCruisingStateType::IDLE_0, std::move(idle_to_table));
            GetSwtichTable().AddStateSwitch(AvpCruisingStateType::STANDBY_1, std::move(standby_to_table));
            GetSwtichTable().AddStateSwitch(AvpCruisingStateType::LOCATING_2, std::move(locating_to_table));
            GetSwtichTable().AddStateSwitch(AvpCruisingStateType::LOCATED_3, std::move(located_to_table));
            GetSwtichTable().AddStateSwitch(AvpCruisingStateType::PREPARED_4, std::move(prepared_to_table));
            GetSwtichTable().AddStateSwitch(AvpCruisingStateType::CRUISING_5, std::move(cruising_to_table));
            GetSwtichTable().AddStateSwitch(AvpCruisingStateType::PARKING_6, std::move(parking_to_table));
            GetSwtichTable().AddStateSwitch(AvpCruisingStateType::OVERRIDE_7, std::move(override_to_table));
            GetSwtichTable().AddStateSwitch(AvpCruisingStateType::SUCCESS_8, std::move(success_to_table));
            GetSwtichTable().AddStateSwitch(AvpCruisingStateType::FAILED_9, std::move(failed_to_table));
            GetSwtichTable().AddStateSwitch(AvpCruisingStateType::SUSPEND_10, std::move(suspend_to_table));
            GetSwtichTable().AddStateSwitch(AvpCruisingStateType::TERMINATE_11, std::move(terminate_to_table));
        };

    public:
        static bool IsRunning() noexcept
        {
            return GetCrntState() >= AvpCruisingStateType::STANDBY_1;
        }
        void PrintStateSwitchInfo() override
        {
            std::cout << "[AVPC] Crnt : " << AvpCruisingFormator(avp_cruising_str_map.at(GetCrntState()))
                      << ", Last : " << AvpCruisingFormator(avp_cruising_str_map.at(GetLastState()))
                      << ", Prvs : " << AvpCruisingFormator(avp_cruising_str_map.at(GetPrvsState()))
                      << ", Duration : " << GetDuration().count() << "(S)" << std::endl;
        }
    };
};
