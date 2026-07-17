#pragma once

#include "avp_cruising_input.h"
#include "avp_cruising_output.h"
#include "avp_cruising_param.h"
#include "state_machine_base.h"
#include "log_base.h"
#include "str_map.h"
#include "state_switch_table.h"

#include <stdint.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <functional>

const std::string AvpFormator(const std::string& str)
{
    return Format(str, avp_cruising_str_map);
}

// 对于std::thread对象而言，其在被析构之前必须确定是汇合还是分离
auto thread_deleter = [](std::thread * p)
{
    if (p)
    {
        if (p->joinable())
        {
            p->join();
        }
        delete p;
    }
};
using thread_uptr_with_deleter = std::unique_ptr<std::thread, decltype(thread_deleter)>;

template <typename T>
using atomic_sptr = std::atomic<std::shared_ptr<AvpCruisingParam>>;

// 但理论上
class AvpCruisingStateMachine : StateMachineBase<AvpCruisingStateType>
{
public:
    using SwitchSubTable = StateSwitchTable<AvpCruisingStateType>::SwitchSubTable;
public:
    struct AvpCruisingPrinter : public DefaultPrinter
    {
        void operator()(const StateMachineBase<AvpCruisingStateType>& base) const override
        {
            std::cout << "[Avp] Crnt State : " << AvpFormator(avp_cruising_str_map.at(base.GetCrntState())) 
                << ", Last State : " << AvpFormator(avp_cruising_str_map.at(base.GetLastState()))
                << ", Prvs State : " << AvpFormator(avp_cruising_str_map.at(base.GetPrvsState())) 
                << ", Duration : " << base.GetDuration().count() << "(S)" << std::endl; 
        }
    };
public:
    // 这里感觉最终的方案还是将状态机基类构建成一个单例基类
    static std::unique_ptr<AvpCruisingStateMachine>& GetInstance()
    {
        static std::unique_ptr<AvpCruisingStateMachine> avp_sm_uptr_(new AvpCruisingStateMachine);
        return avp_sm_uptr_;
    }
private:
    thread_uptr_with_deleter trd_{nullptr, thread_deleter};
    // atomic_sptr<AvpCruisingParam> param_;
    std::shared_ptr<AvpCruisingInput> input_;
    // atomic_sptr<AvpCruisingOutput> output_;
    StateSwitchTable<AvpCruisingStateType> table_;

    std::multimap<AvpCruisingStateType, std::pair<AvpCruisingStateType, std::function<bool(AvpCruisingStateType)>>> state_switch_map_;
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
private:
    AvpCruisingStateMachine(PrinterType<AvpCruisingStateType> func = AvpCruisingPrinter()) : StateMachineBase("AvpCruising", func)
    {
        SetEnableFlag(true);

        InitStateSwtichTable();
    }
    AvpCruisingStateMachine(const AvpCruisingStateMachine&) = delete;
    AvpCruisingStateMachine& operator=(const AvpCruisingStateMachine&) = delete;
public:
    ~AvpCruisingStateMachine()
    {
        SetSetupFlag(false);
    }
    void InitStateSwtichTable()
    {
        SwitchSubTable idle_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateMachine::SwitchFromStandbyToIdle, this)},
        };
         
        SwitchSubTable standby_to_table = 
        {
            {AvpCruisingStateType::IDLE_0, std::bind(&AvpCruisingStateMachine::SwitchFromStandbyToIdle, this)},
            {AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingStateMachine::SwitchFromStandbyToLocating, this)},
        };

        SwitchSubTable locating_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateMachine::SwitchFromLocatingToStandby, this)},
            {AvpCruisingStateType::LOCATED_3, std::bind(&AvpCruisingStateMachine::SwitchFromLocatingToLocated, this)},
        };

        SwitchSubTable located_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateMachine::SwitchFromLocatedToStandby, this)},
            {AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingStateMachine::SwitchFromLocatedToLocating, this)},
            {AvpCruisingStateType::PREPARED_4, std::bind(&AvpCruisingStateMachine::SwitchFromLocatedToPrepared, this)},
        };

        SwitchSubTable prepared_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateMachine::SwitchFromPreparedToStandby, this)},
            {AvpCruisingStateType::LOCATING_2, std::bind(&AvpCruisingStateMachine::SwitchFromPreparedToLocating, this)},
            {AvpCruisingStateType::LOCATED_3, std::bind(&AvpCruisingStateMachine::SwitchFromPreparedToLocated, this)},
            {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateMachine::SwitchFromPreparedToCruising, this)},
        };

        SwitchSubTable cruising_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateMachine::SwitchFromCruisingToStandby, this)},
            {AvpCruisingStateType::PARKING_6, std::bind(&AvpCruisingStateMachine::SwitchFromCruisingToParking, this)},
            {AvpCruisingStateType::OVERRIDE_7, std::bind(&AvpCruisingStateMachine::SwitchFromCruisingToOverride, this)},
            {AvpCruisingStateType::SUCCESS_8, std::bind(&AvpCruisingStateMachine::SwitchFromCruisingToSuccess, this)},
            {AvpCruisingStateType::FAILED_9, std::bind(&AvpCruisingStateMachine::SwitchFromCruisingToFailed, this)},
            {AvpCruisingStateType::SUSPEND_10, std::bind(&AvpCruisingStateMachine::SwitchFromCruisingToSuspend, this)},
            {AvpCruisingStateType::TERMINATE_11, std::bind(&AvpCruisingStateMachine::SwitchFromCruisingToTerminate, this)},
        };

        SwitchSubTable parking_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateMachine::SwitchFromParkingToStandby, this)},
            {AvpCruisingStateType::SUCCESS_8, std::bind(&AvpCruisingStateMachine::SwitchFromParkingToSuccess, this)},
            {AvpCruisingStateType::FAILED_9, std::bind(&AvpCruisingStateMachine::SwitchFromParkingToFailed, this)},
            {AvpCruisingStateType::SUSPEND_10, std::bind(&AvpCruisingStateMachine::SwitchFromParkingToSuspend, this)},
            {AvpCruisingStateType::TERMINATE_11, std::bind(&AvpCruisingStateMachine::SwitchFromParkingToTerminate, this)},
        };

        SwitchSubTable override_to_table = 
        {
            {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateMachine::SwitchFromOverrideToStandby, this)},
            {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateMachine::SwitchFromOverrideToCruising, this)},
        };

        SwitchSubTable success_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateMachine::SwitchFromSuccessToStandby, this)},
        };

        SwitchSubTable failed_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateMachine::SwitchFromFailedToStandby, this)},
        };

        SwitchSubTable suspend_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateMachine::SwitchFromSuspenedToStandby, this)},
            {AvpCruisingStateType::CRUISING_5, std::bind(&AvpCruisingStateMachine::SwitchFromSuspenedToCruising, this)},
            {AvpCruisingStateType::PARKING_6, std::bind(&AvpCruisingStateMachine::SwitchFromSuspenedToParking, this)},
            {AvpCruisingStateType::TERMINATE_11, std::bind(&AvpCruisingStateMachine::SwitchFromSuspenedToTerminate, this)},
        };

        SwitchSubTable terminate_to_table = 
        {
            {AvpCruisingStateType::STANDBY_1, std::bind(&AvpCruisingStateMachine::SwitchFromTerminateToStandby, this)},
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
    }
    AvpCruisingStateType CalcCrntState() const noexcept override
    {
        AvpCruisingStateType crnt_state = GetCrntState();
        auto to_state_list = table_.GetSwitchTable(crnt_state);
        for (auto iter = std::begin(to_state_list); iter != std::end(to_state_list); ++iter)
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
    }
public:
    void Run() override
    {
        // uint32_t count = 20;
        while (true)
        {  
            auto state = CalcCrntState();
            std::cout << "crnt state : " << static_cast<uint32_t>(state) << std::endl;
            UpdateState(state);
            PrintData();

            // std::cout << "[Avp] Crnt State : " << AvpFormator(avp_cruising_str_map.at(GetCrntState())) 
            // << ", Last State : " << AvpFormator(avp_cruising_str_map.at(GetLastState()))
            // << ", Prvs State : " << AvpFormator(avp_cruising_str_map.at(GetPrvsState())) 
            // << ", Duration : " << GetDuration().count() << "(S)" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            // if (count == 0)
            // {
            //     break;
            // }
            // else
            // {
            //     count--;
            // }
        }
        
    }
    void Init() override
    {
        if (LoadFunctionParam() && CreateReadersAndWriters())
        {
            SetInitFlag(true);
        }
        else
        {
            SetInitFlag(false);
        }
    }
    void Setup() noexcept
    {
        if (GetEnableFlag())
        {
            Init();
        }
        if (GetInitFlag())
        {
            trd_.reset(new std::thread(&AvpCruisingStateMachine::Run, this));
            if (trd_)
            {
                std::cout << "Create AvpCruisingStateMachine object thread!" << std::endl;
            }
            else
            {
                SetSetupFlag(false);
            }
        }
        
    }
private:
    bool LoadFunctionSwitchParam()
    {
        return true;
    }
    bool LoadFunctionValueParam()
    {
        return true;
    }
    bool LoadFunctionParam()
    {
        return LoadFunctionSwitchParam() && LoadFunctionValueParam();
    }
    bool CreateReaders()
    {
        return true;
    }
    bool CreateWriters()
    {
        return true;
    }
    bool CreateReadersAndWriters()
    {
        return CreateReaders() && CreateWriters();
    }
};