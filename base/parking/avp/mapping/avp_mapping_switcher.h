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
class AvpMappingStateSwitcher : public StateMachineSwitcherBase<AvpMappingStateType, AvpMappingParam, AvpMappingInputer>
{
private:
    StateSwitchTable<AvpMappingStateType, AvpMappingParam, AvpMappingInputer> table_;
public:
    AvpMappingStateSwitcher() : StateMachineSwitcherBase<AvpMappingStateType, AvpMappingParam, AvpMappingInputer>()
    {

    }
private:
    bool SwitchFromIdleToStandby(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
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
    bool SwitchFromStandbyToIdle(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
    {
        return false;
    }
    bool SwitchFromStandbyToOnlineLearning(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
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
    bool SwitchFromOnlineLearningToOfflineLearning(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
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
    bool SwitchFromOnlineLearningToParking(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
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
    bool SwitchFromOnlineLearningToTerminate(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
    {
        return false;
    }
    bool SwitchFromOfflineLearningToSuccess(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
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
    bool SwitchFromOfflineLearningToFailure(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
    {
        return false;
    }
    bool SwitchFromOfflineLearningToTerminate(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
    {
        return false;
    }
    bool SwitchFromParkingToOfflineLearning(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
    {
        return false;
    }
    bool SwitchFromParkingToTerminate(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
    {
        return false;
    }
    bool SwitchFromSuccessToStandby(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
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
    bool SwitchFromFailedToStandby(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
    {
        return false;
    }
    bool SwitchFromTerminateToStandby(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) const noexcept
    {
        return false;
    }

public:
    void Init() override 
    {
        using SwitchSubTable = StateSwitchTable<AvpMappingStateType, AvpMappingParam, AvpMappingInputer>::SwitchSubTable;

        SwitchSubTable idle_to_table = 
        {
            {AvpMappingStateType::STANDBY_1, std::bind(&AvpMappingStateSwitcher::SwitchFromIdleToStandby, this, std::placeholders::_1, std::placeholders::_2)},
        };
         
        SwitchSubTable standby_to_table = 
        {
            {AvpMappingStateType::IDLE_0, std::bind(&AvpMappingStateSwitcher::SwitchFromStandbyToIdle, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpMappingStateType::ONLINE_LEARNING_2, std::bind(&AvpMappingStateSwitcher::SwitchFromStandbyToOnlineLearning, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable online_learning_to_table = 
        {
            {AvpMappingStateType::OFFLINE_LEARNING_3, std::bind(&AvpMappingStateSwitcher::SwitchFromOnlineLearningToOfflineLearning, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpMappingStateType::PARKING_4, std::bind(&AvpMappingStateSwitcher::SwitchFromOnlineLearningToParking, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpMappingStateType::TERMINATE_7, std::bind(&AvpMappingStateSwitcher::SwitchFromOnlineLearningToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable offline_learning_to_table = 
        {
            {AvpMappingStateType::SUCCESS_5, std::bind(&AvpMappingStateSwitcher::SwitchFromOfflineLearningToSuccess, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpMappingStateType::FAILED_6, std::bind(&AvpMappingStateSwitcher::SwitchFromOfflineLearningToFailure, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpMappingStateType::TERMINATE_7, std::bind(&AvpMappingStateSwitcher::SwitchFromOfflineLearningToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable parking_to_table = 
        {
            {AvpMappingStateType::OFFLINE_LEARNING_3, std::bind(&AvpMappingStateSwitcher::SwitchFromParkingToOfflineLearning, this, std::placeholders::_1, std::placeholders::_2)},
            {AvpMappingStateType::TERMINATE_7, std::bind(&AvpMappingStateSwitcher::SwitchFromParkingToTerminate, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable success_to_table = 
        {
            {AvpMappingStateType::STANDBY_1, std::bind(&AvpMappingStateSwitcher::SwitchFromSuccessToStandby, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable failed_to_table = 
        {
            {AvpMappingStateType::STANDBY_1, std::bind(&AvpMappingStateSwitcher::SwitchFromFailedToStandby, this, std::placeholders::_1, std::placeholders::_2)},
        };

        SwitchSubTable terminate_to_table = 
        {
            {AvpMappingStateType::STANDBY_1, std::bind(&AvpMappingStateSwitcher::SwitchFromTerminateToStandby, this, std::placeholders::_1, std::placeholders::_2)},
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
    AvpMappingStateType CalcNextState(std::shared_ptr<AvpMappingParam> param, std::shared_ptr<AvpMappingInputer> input) override
    {
        auto crnt_state = GetCrntState();
        auto state_switch_list = table_.GetStateSwitchTable(crnt_state);
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
