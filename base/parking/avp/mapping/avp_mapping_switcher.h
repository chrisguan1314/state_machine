#pragma once

#include "../../../../enum.h"
#include "../../../../str_map.h"
#include "../../../state_machine_switcher_base.h"
#include "../../../state_switch_table.h"
#include "avp_mapping_inputer.h"
#include "avp_mapping_param.h"
#include "../.././../base.h"

namespace parking
{
const std::string AvpMappingFormator(const std::string& str)
{
    return Format(str, avp_mapping_str_map);
}
class AvpMappingStateSwitcher : public StateMachineSwitcherBase<AvpMappingStateType>
{
private:
    StateSwitchTable<AvpMappingStateType> table_;
public:
    AvpMappingStateSwitcher() : StateMachineSwitcherBase<AvpMappingStateType>()
    {

    }
private:
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
    bool SwitchFromStandbyToIdle() const noexcept
    {
        return false;
    }
    bool SwitchFromStandbyToOnlineLearning() const noexcept
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
    bool SwitchFromOnlineLearningToOfflineLearning() const noexcept
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
    bool SwitchFromOnlineLearningToParking() const noexcept
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
    bool SwitchFromOnlineLearningToTerminate() const noexcept
    {
        return false;
    }
    bool SwitchFromOfflineLearningToSuccess() const noexcept
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
    bool SwitchFromOfflineLearningToFailure() const noexcept
    {
        return false;
    }
    bool SwitchFromOfflineLearningToTerminate() const noexcept
    {
        return false;
    }
    bool SwitchFromParkingToOfflineLearning() const noexcept
    {
        return false;
    }
    bool SwitchFromParkingToTerminate() const noexcept
    {
        return false;
    }
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
        using SwitchSubTable = StateSwitchTable<AvpMappingStateType>::SwitchSubTable;

        SwitchSubTable idle_to_table = 
        {
            {AvpMappingStateType::STANDBY_1, std::bind(&AvpMappingStateSwitcher::SwitchFromIdleToStandby, this)},
        };
         
        SwitchSubTable standby_to_table = 
        {
            {AvpMappingStateType::IDLE_0, std::bind(&AvpMappingStateSwitcher::SwitchFromStandbyToIdle, this)},
            {AvpMappingStateType::ONLINE_LEARNING_2, std::bind(&AvpMappingStateSwitcher::SwitchFromStandbyToOnlineLearning, this)},
        };

        SwitchSubTable online_learning_to_table = 
        {
            {AvpMappingStateType::OFFLINE_LEARNING_3, std::bind(&AvpMappingStateSwitcher::SwitchFromOnlineLearningToOfflineLearning, this)},
            {AvpMappingStateType::PARKING_4, std::bind(&AvpMappingStateSwitcher::SwitchFromOnlineLearningToParking, this)},
            {AvpMappingStateType::TERMINATE_7, std::bind(&AvpMappingStateSwitcher::SwitchFromOnlineLearningToTerminate, this)},
        };

        SwitchSubTable offline_learning_to_table = 
        {
            {AvpMappingStateType::SUCCESS_5, std::bind(&AvpMappingStateSwitcher::SwitchFromOfflineLearningToSuccess, this)},
            {AvpMappingStateType::FAILED_6, std::bind(&AvpMappingStateSwitcher::SwitchFromOfflineLearningToFailure, this)},
            {AvpMappingStateType::TERMINATE_7, std::bind(&AvpMappingStateSwitcher::SwitchFromOfflineLearningToTerminate, this)},
        };

        SwitchSubTable parking_to_table = 
        {
            {AvpMappingStateType::OFFLINE_LEARNING_3, std::bind(&AvpMappingStateSwitcher::SwitchFromParkingToOfflineLearning, this)},
            {AvpMappingStateType::TERMINATE_7, std::bind(&AvpMappingStateSwitcher::SwitchFromParkingToTerminate, this)},
        };

        SwitchSubTable success_to_table = 
        {
            {AvpMappingStateType::STANDBY_1, std::bind(&AvpMappingStateSwitcher::SwitchFromSuccessToStandby, this)},
        };

        SwitchSubTable failed_to_table = 
        {
            {AvpMappingStateType::STANDBY_1, std::bind(&AvpMappingStateSwitcher::SwitchFromFailedToStandby, this)},
        };

        SwitchSubTable terminate_to_table = 
        {
            {AvpMappingStateType::STANDBY_1, std::bind(&AvpMappingStateSwitcher::SwitchFromTerminateToStandby, this)},
        };

        table_.AddStateSwitch(AvpMappingStateType::IDLE_0, std::move(idle_to_table));
        table_.AddStateSwitch(AvpMappingStateType::STANDBY_1, std::move(standby_to_table));
        table_.AddStateSwitch(AvpMappingStateType::ONLINE_LEARNING_2, std::move(online_learning_to_table));
        table_.AddStateSwitch(AvpMappingStateType::OFFLINE_LEARNING_3, std::move(offline_learning_to_table));
        table_.AddStateSwitch(AvpMappingStateType::PARKING_4, std::move(parking_to_table));
        table_.AddStateSwitch(AvpMappingStateType::SUCCESS_5, std::move(success_to_table));
        table_.AddStateSwitch(AvpMappingStateType::FAILED_6, std::move(failed_to_table));
        table_.AddStateSwitch(AvpMappingStateType::TERMINATE_7, std::move(terminate_to_table));
    }; 
public:
    AvpMappingStateType CalcNextState() override
    {
        auto crnt_state = GetCrntState();
        auto state_switch_list = table_.GetStateSwitchTable(crnt_state);
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
    static bool IsRunning() noexcept
    {
        return GetCrntState() >= AvpMappingStateType::STANDBY_1;
    }
    void PrintStateSwitchInfo() override
    {
        std::cout << "[AVPM] Crnt : " << AvpMappingFormator(avp_mapping_str_map.at(GetCrntState())) 
            << ", Last : " << AvpMappingFormator(avp_mapping_str_map.at(GetLastState()))
            << ", Prvs : " << AvpMappingFormator(avp_mapping_str_map.at(GetPrvsState())) 
            << ", Duration : " << GetDuration().count() << "(S)" << std::endl;
    }
};
};
