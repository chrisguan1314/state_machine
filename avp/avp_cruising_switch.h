#pragma once

#include "../state_machine_switch_base.h"
#include "../state_switch_table.h"

namespace avp_cruising
{
const std::string AvpFormator(const std::string& str)
{
    return Format(str, avp_cruising_str_map);
}
class AvpCruisingStateSwitch : public StateMachineSwtichBase<AvpCruisingStateType>
{
private:
    StateSwitchTable<AvpCruisingStateType> table_;
public:
    AvpCruisingStateSwitch() : StateMachineSwtichBase<AvpCruisingStateType>()
    {

    }
private:
    // *******************************SwitchFromIdle*******************************
    bool SwitchFromIdleToStandby() const noexcept
    {
        return true;
    }
    // *******************************SwitchFromStandby*******************************
    bool SwitchFromStandbyToIdle() const noexcept
    {
        return true;
    }
    bool SwitchFromStandbyToLocating() const noexcept
    {
        return true;
    }
    // *******************************SwitchFromLocating*******************************
    bool SwitchFromLocatingToStandby() const noexcept
    {
        return true;
    }
    bool SwitchFromLocatingToLocated() const noexcept
    {
        return true;
    }
    // *******************************SwitchFromLocated*******************************
    bool SwitchFromLocatedToStandby() const noexcept
    {
        return true;
    }
    bool SwitchFromLocatedToLocating() const noexcept
    {
        return true;
    }
    bool SwitchFromLocatedToPrepared() const noexcept
    {
        return true;
    }
    // *******************************SwitchFromPrepared*******************************
    bool SwitchFromPreparedToStandby() const noexcept
    {
        return true;
    }
    bool SwitchFromPreparedToLocating() const noexcept
    {
        return true;
    }
    bool SwitchFromPreparedToLocated() const noexcept
    {
        return true;
    }
    bool SwitchFromPreparedToCruising() const noexcept
    {
        return true;
    }
    // *******************************SwitchFromCruising*******************************
    bool SwitchFromCruisingToStandby() const noexcept
    {
        return true;
    }
    bool SwitchFromCruisingToParking() const noexcept
    {
        return true;
    }
    bool SwitchFromCruisingToOverride() const noexcept
    {
        return true;
    }
    bool SwitchFromCruisingToSuccess() const noexcept
    {
        return true;
    }
    bool SwitchFromCruisingToFailed() const noexcept
    {
        return true;
    }
    bool SwitchFromCruisingToSuspend() const noexcept
    {
        return true;
    }
    bool SwitchFromCruisingToTerminate() const noexcept
    {
        return true;
    }
    // *******************************SwitchFromParking*******************************
    bool SwitchFromParkingToStandby() const noexcept
    {
        return true;
    }
    bool SwitchFromParkingToSuccess() const noexcept
    {
        return true;
    }
    bool SwitchFromParkingToFailed() const noexcept
    {
        return true;
    }
    bool SwitchFromParkingToSuspend() const noexcept
    {
        return true;
    }
    bool SwitchFromParkingToTerminate() const noexcept
    {
        return true;
    }
    // *******************************SwitchFromOverride*******************************
    bool SwitchFromOverrideToStandby() const noexcept
    {
        return true;
    }
    bool SwitchFromOverrideToCruising() const noexcept
    {
        return true;
    }
    // *******************************SwitchFromSuccess*******************************
    bool SwitchFromSuccessToStandby() const noexcept
    {
        return true;
    }
    // *******************************SwitchFromFailed*******************************
    bool SwitchFromFailedToStandby() const noexcept
    {
        return true;
    }
    // *******************************SwitchFromSuspend*******************************
    bool SwitchFromSuspenedToStandby() const noexcept
    {
        return true;
    }
    bool SwitchFromSuspenedToCruising() const noexcept
    {
        return true;
    }
    bool SwitchFromSuspenedToParking() const noexcept
    {
        return true;
    }
    bool SwitchFromSuspenedToTerminate() const noexcept
    {
        return true;
    }
    // *******************************SwitchFromgTerminate*******************************
    bool SwitchFromTerminateToStandby() const noexcept
    {
        return true;
    }
public:
    void Init() override 
    {
        using SwitchSubTable = StateSwitchTable<AvpCruisingStateType>::SwitchSubTable;

        SwitchSubTable idle_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitch::SwitchFromStandbyToIdle, this)},
        };
         
        SwitchSubTable standby_to_table = 
        {
            {AvpCruisingStateType::IDLE_0, std::bind(&AvpCruisingStateSwitch::SwitchFromStandbyToIdle, this)},
            {AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingStateSwitch::SwitchFromStandbyToLocating, this)},
        };

        SwitchSubTable locating_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitch::SwitchFromLocatingToStandby, this)},
            {AvpCruisingStateType::LOCATED_3, std::bind(&AvpCruisingStateSwitch::SwitchFromLocatingToLocated, this)},
        };

        SwitchSubTable located_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitch::SwitchFromLocatedToStandby, this)},
            {AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingStateSwitch::SwitchFromLocatedToLocating, this)},
            {AvpCruisingStateType::PREPARED_4, std::bind(&AvpCruisingStateSwitch::SwitchFromLocatedToPrepared, this)},
        };

        SwitchSubTable prepared_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitch::SwitchFromPreparedToStandby, this)},
            {AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingStateSwitch::SwitchFromPreparedToLocating, this)},
            {AvpCruisingStateType::LOCATED_3, std::bind(&AvpCruisingStateSwitch::SwitchFromPreparedToLocated, this)},
            {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateSwitch::SwitchFromPreparedToCruising, this)},
        };

        SwitchSubTable cruising_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitch::SwitchFromCruisingToStandby, this)},
            {AvpCruisingStateType::PARKING_6, std::bind(&AvpCruisingStateSwitch::SwitchFromCruisingToParking, this)},
            {AvpCruisingStateType::OVERRIDE_7, std::bind(&AvpCruisingStateSwitch::SwitchFromCruisingToOverride, this)},
            {AvpCruisingStateType::SUCCESS_8, std::bind(&AvpCruisingStateSwitch::SwitchFromCruisingToSuccess, this)},
            {AvpCruisingStateType::FAILED_9, std::bind(&AvpCruisingStateSwitch::SwitchFromCruisingToFailed, this)},
            {AvpCruisingStateType::SUSPEND_10, std::bind(&AvpCruisingStateSwitch::SwitchFromCruisingToSuspend, this)},
            {AvpCruisingStateType::TERMINATE_11, std::bind(&AvpCruisingStateSwitch::SwitchFromCruisingToTerminate, this)},
        };

        SwitchSubTable parking_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitch::SwitchFromParkingToStandby, this)},
            {AvpCruisingStateType::SUCCESS_8, std::bind(&AvpCruisingStateSwitch::SwitchFromParkingToSuccess, this)},
            {AvpCruisingStateType::FAILED_9, std::bind(&AvpCruisingStateSwitch::SwitchFromParkingToFailed, this)},
            {AvpCruisingStateType::SUSPEND_10, std::bind(&AvpCruisingStateSwitch::SwitchFromParkingToSuspend, this)},
            {AvpCruisingStateType::TERMINATE_11, std::bind(&AvpCruisingStateSwitch::SwitchFromParkingToTerminate, this)},
        };

        SwitchSubTable override_to_table = 
        {
            {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateSwitch::SwitchFromOverrideToStandby, this)},
            {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateSwitch::SwitchFromOverrideToCruising, this)},
        };

        SwitchSubTable success_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitch::SwitchFromSuccessToStandby, this)},
        };

        SwitchSubTable failed_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitch::SwitchFromFailedToStandby, this)},
        };

        SwitchSubTable suspend_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitch::SwitchFromSuspenedToStandby, this)},
            {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateSwitch::SwitchFromSuspenedToCruising, this)},
            {AvpCruisingStateType::PARKING_6, std::bind(&AvpCruisingStateSwitch::SwitchFromSuspenedToParking, this)},
            {AvpCruisingStateType::TERMINATE_11, std::bind(&AvpCruisingStateSwitch::SwitchFromSuspenedToTerminate, this)},
        };

        SwitchSubTable terminate_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateSwitch::SwitchFromTerminateToStandby, this)},
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
    AvpCruisingStateType CalcNextState(std::shared_ptr<StateMachineInputBase> input) override
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
