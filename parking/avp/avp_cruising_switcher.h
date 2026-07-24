#pragma once

#include "../../base/state_machine_switcher_base.h"
#include "../../base/state_switch_table.h"

#include <any>

namespace parking
{
const std::string AvpFormator(const std::string& str)
{
    return Format(str, avp_cruising_str_map);
}
class AvpCruisingStateSwitcher : public StateMachineSwitcherBase<AvpCruisingStateType, AvpCruisingParam, AvpCruisingInputer>
{
private:
    StateSwitchTable<AvpCruisingStateType, AvpCruisingParam, AvpCruisingInputer> table_;
public:
    AvpCruisingStateSwitcher() : StateMachineSwitcherBase<AvpCruisingStateType, AvpCruisingParam, AvpCruisingInputer>()
    {

    }
private:
    // *******************************SwitchFromIdle*******************************
    bool SwitchFromIdleToStandby(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
    {
        if (GetCount() > (20 * 5))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // *******************************SwitchFromStandby*******************************
    bool SwitchFromStandbyToIdle(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
    {
        if (GetCount() > (20 * 5))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchFromStandbyToLocating(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
    {
        if (GetCount() > (20 * 5))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // *******************************SwitchFromLocating*******************************
    bool SwitchFromLocatingToStandby(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromLocatingToLocated(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromLocatedToStandby(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromLocatedToLocating(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromLocatedToPrepared(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromPreparedToStandby(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromPreparedToLocating(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromPreparedToLocated(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromPreparedToCruising(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromCruisingToStandby(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromCruisingToParking(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromCruisingToOverride(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromCruisingToSuccess(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromCruisingToFailed(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromCruisingToSuspend(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromCruisingToTerminate(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromParkingToStandby(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromParkingToSuccess(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromParkingToFailed(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromParkingToSuspend(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromParkingToTerminate(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromOverrideToStandby(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromOverrideToCruising(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromSuccessToStandby(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromFailedToStandby(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromSuspenedToStandby(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromSuspenedToCruising(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromSuspenedToParking(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
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
    bool SwitchFromSuspenedToTerminate(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
    {
        if (GetCount() > (20 * 30))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // *******************************SwitchFromgTerminate*******************************
    bool SwitchFromTerminateToStandby(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) const noexcept
    {
        if (GetCount() > (20 * 3))
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
        using SwitchSubTable = StateSwitchTable<AvpCruisingStateType, AvpCruisingParam, AvpCruisingInputer>::SwitchSubTable;

        SwitchSubTable idle_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromStandbyToIdle, this, std::placeholders::_1, std::placeholders::_2)},
        };
         
        SwitchSubTable standby_to_table = 
        {
            {AvpCruisingStateType::IDLE_0, std::bind(&AvpCruisingStateSwitcher::SwitchFromStandbyToIdle, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingStateSwitcher::SwitchFromStandbyToLocating, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable locating_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromLocatingToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::LOCATED_3, std::bind(&AvpCruisingStateSwitcher::SwitchFromLocatingToLocated, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable located_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromLocatedToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingStateSwitcher::SwitchFromLocatedToLocating, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::PREPARED_4, std::bind(&AvpCruisingStateSwitcher::SwitchFromLocatedToPrepared, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable prepared_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromPreparedToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingStateSwitcher::SwitchFromPreparedToLocating, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::LOCATED_3, std::bind(&AvpCruisingStateSwitcher::SwitchFromPreparedToLocated, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateSwitcher::SwitchFromPreparedToCruising, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable cruising_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::PARKING_6, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToParking, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::OVERRIDE_7, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToOverride, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::SUSPEND_8, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToSuspend, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::TERMINATE_9, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::SUCCESS_10, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToSuccess, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::FAILED_11, std::bind(&AvpCruisingStateSwitcher::SwitchFromCruisingToFailed, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable parking_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromParkingToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::SUSPEND_8, std::bind(&AvpCruisingStateSwitcher::SwitchFromParkingToSuspend, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::TERMINATE_9, std::bind(&AvpCruisingStateSwitcher::SwitchFromParkingToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::SUCCESS_10, std::bind(&AvpCruisingStateSwitcher::SwitchFromParkingToSuccess, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::FAILED_11, std::bind(&AvpCruisingStateSwitcher::SwitchFromParkingToFailed, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable override_to_table = 
        {
            {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateSwitcher::SwitchFromOverrideToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateSwitcher::SwitchFromOverrideToCruising, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable success_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromSuccessToStandby, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable failed_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromFailedToStandby, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable suspend_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromSuspenedToStandby, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateSwitcher::SwitchFromSuspenedToCruising, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::PARKING_6, std::bind(&AvpCruisingStateSwitcher::SwitchFromSuspenedToParking, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpCruisingStateType::TERMINATE_9, std::bind(&AvpCruisingStateSwitcher::SwitchFromSuspenedToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable terminate_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitcher::SwitchFromTerminateToStandby, this, std::placeholders::_1, std::placeholders::_2)},
        };

        table_.AddStateSwitch(AvpCruisingStateType::IDLE_0, idle_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::STANDBY_1, standby_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::LOCATING_2, locating_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::LOCATED_3, located_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::PREPARED_4, prepared_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::CRUISING_5, cruising_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::PARKING_6, parking_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::OVERRIDE_7, override_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::SUSPEND_8, suspend_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::TERMINATE_9, terminate_to_table);
        table_.AddStateSwitch(AvpCruisingStateType::SUCCESS_10, success_to_table); 
        table_.AddStateSwitch(AvpCruisingStateType::FAILED_11, failed_to_table);
        std::cout << "Init AvpCruisingStateSwitcher StateSwitchTable" << std::endl;
    }; 
public:
    AvpCruisingStateType CalcNextState(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input) override
    {
        auto crnt_state = GetCrntState();
        auto state_switch_list = table_.GetSubStateSwitchTable(crnt_state);
        for (auto iter = std::begin(state_switch_list); iter != std::end(state_switch_list); ++iter)
        {
            auto to_state = iter->first;
            auto switch_function = iter->second;
            if (switch_function(param, input))
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
