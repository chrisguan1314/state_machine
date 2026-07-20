#pragma once

#include "../base/state_machine_switcher_base.h"
#include "../base/state_switch_table.h"

namespace parking
{
const std::string AvpFormator(const std::string& str)
{
    return Format(str, avp_cruising_str_map);
}
class AvpCruisingStateSwitcher : public StateMachineSwticherBase<AvpCruisingStateType>
{
private:
    StateSwitchTable<AvpCruisingStateType> table_;
public:
    AvpCruisingStateSwitcher() : StateMachineSwticherBase<AvpCruisingStateType>()
    {

    }
private:
    // *******************************SwitchFromIdle*******************************
    bool SwitchFromIdleToStandby() const noexcept
    {
        if (GetCount() > 20)
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
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromStandbyToLocating() const noexcept
    {
        if (GetCount() > 20)
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
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromLocatingToLocated() const noexcept
    {
        if (GetCount() > 20)
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
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromLocatedToLocating() const noexcept
    {
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromLocatedToPrepared() const noexcept
    {
        if (GetCount() > 20)
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
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromPreparedToLocating() const noexcept
    {
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromPreparedToLocated() const noexcept
    {
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromPreparedToCruising() const noexcept
    {
        if (GetCount() > 20)
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
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromCruisingToParking() const noexcept
    {
        if (GetCount() > 20)
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
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromCruisingToSuccess() const noexcept
    {
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromCruisingToFailed() const noexcept
    {
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromCruisingToSuspend() const noexcept
    {
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromCruisingToTerminate() const noexcept
    {
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // *******************************SwitchFromParking*******************************
    bool SwitchFromParkingToStandby() const noexcept
    {
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromParkingToSuccess() const noexcept
    {
        if (GetCount() > 20)
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
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromParkingToSuspend() const noexcept
    {
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromParkingToTerminate() const noexcept
    {
        if (GetCount() > 20)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // *******************************SwitchFromOverride*******************************
    bool SwitchFromOverrideToStandby() const noexcept
    {
        if (GetCount() > 20)
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
        if (GetCount() > 20)
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
        if (GetCount() > 20)
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
        if (GetCount() > 20)
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
        if (GetCount() > 20)
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
        if (GetCount() > 20)
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
        if (GetCount() > 20)
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
        if (GetCount() > 20)
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
        if (GetCount() > 20)
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
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromStandbyToIdle, this)},
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

        table_.AddStateSwitch(AvpCruisingStateType::IDLE_0, idle_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::STANDBY_1, standby_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::LOCATING_2, locating_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::LOCATED_3, located_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::PREPARED_4, prepared_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::CRUISING_5, cruising_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::PARKING_6, parking_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::OVERRIDE_7, override_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::SUCCESS_8, success_to_table); 
        table_.AddStateSwitch(AvpCruisingStateType::FAILED_9, failed_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::SUSPEND_10, suspend_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::TERMINATE_11, terminate_to_table);
    }; 
public:
    AvpCruisingStateType CalcNextState(std::shared_ptr<StateMachineInputerBase> input) override
    {
        auto crnt_state = GetCrntState();
        auto state_switch_list = table_.GetSwitchTable(crnt_state);
        for (auto iter = std::begin(state_switch_list); iter != std::end(state_switch_list); ++iter)
        {
            auto to_state = iter->first;
            auto switch_function = iter->second;
            if (switch_function())
            {
                crnt_state = to_state;
                break;
            }
        }
        return crnt_state;
    };
    void PrintStateSwitchInfo() override
    {
        std::cout << "[Avp] Crnt State : " << AvpFormator(avp_cruising_str_map.at(GetCrntState())) 
            << ", Last State : " << AvpFormator(avp_cruising_str_map.at(GetLastState()))
            << ", Prvs State : " << AvpFormator(avp_cruising_str_map.at(GetPrvsState())) 
            << ", Duration : " << GetDuration().count() << "(S)" << std::endl;
    }
};
};
