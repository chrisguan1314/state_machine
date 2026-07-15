#pragma once

#include "avp_cruising_input.h"
#include "avp_cruising_output.h"
#include "avp_cruising_param.h"
#include "state_machine_base.h"
#include "log_base.h"
#include "str_map.h"

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

    std::multimap<AvpCruisingStateType, AvpCruisingStateType> state_switch_map_;
    std::unordered_map<AvpCruisingStateType, std::function<bool(AvpCruisingStateType)>> state_policy_map_;
private:
    bool SwitchToIdle(AvpCruisingStateType type) const noexcept
    {
        if (GetCount() > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchToStandby(AvpCruisingStateType type) const noexcept
    {
        if (GetCount() > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchToLocating(AvpCruisingStateType type) const noexcept
    {
        if (GetCount() > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchToLocated(AvpCruisingStateType type) const noexcept
    {
        if (GetCount() > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchToPrepared(AvpCruisingStateType type) const noexcept
    {
        if (GetCount() > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchToCruising(AvpCruisingStateType type) const noexcept
    {
        if (GetCount() > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchToParking(AvpCruisingStateType type) const noexcept
    {
        if (GetCount() > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchToOverride(AvpCruisingStateType type) const noexcept
    {
        if (GetCount() > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchToSuspend(AvpCruisingStateType type) const noexcept
    {
        if (GetCount() > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchToTerminate(AvpCruisingStateType type) const noexcept
    {
        if (GetCount() > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchToSuccess(AvpCruisingStateType type) const noexcept
    {
        if (GetCount() > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool SwitchToFailed(AvpCruisingStateType type) const noexcept
    {
        if (GetCount() > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
private:
    AvpCruisingStateMachine(PrinterType<AvpCruisingStateType> func = AvpCruisingPrinter()) : StateMachineBase("AvpCruising", func)
    {
        SetEnableFlag(true);

        InitStateSwtichMap();
        InitStatepolicyMap();
    }
    AvpCruisingStateMachine(const AvpCruisingStateMachine&) = delete;
    AvpCruisingStateMachine& operator=(const AvpCruisingStateMachine&) = delete;
public:
    ~AvpCruisingStateMachine()
    {
        SetSetupFlag(false);
    }
    void InitStateSwtichMap()
    {
        state_switch_map_.insert({AvpCruisingStateType::IDLE_0, AvpCruisingStateType::STANDBY_1});

        state_switch_map_.insert({AvpCruisingStateType::STANDBY_1, AvpCruisingStateType::IDLE_0});
        state_switch_map_.insert({AvpCruisingStateType::STANDBY_1, AvpCruisingStateType::LOCATING_2});

        state_switch_map_.insert({AvpCruisingStateType::LOCATING_2, AvpCruisingStateType::STANDBY_1});
        state_switch_map_.insert({AvpCruisingStateType::LOCATING_2, AvpCruisingStateType::LOCATED_3});

        state_switch_map_.insert({AvpCruisingStateType::LOCATED_3, AvpCruisingStateType::STANDBY_1});
        state_switch_map_.insert({AvpCruisingStateType::LOCATED_3, AvpCruisingStateType::LOCATING_2});
        state_switch_map_.insert({AvpCruisingStateType::LOCATED_3, AvpCruisingStateType::PREPARED_4});

        state_switch_map_.insert({AvpCruisingStateType::PREPARED_4, AvpCruisingStateType::STANDBY_1});
        state_switch_map_.insert({AvpCruisingStateType::PREPARED_4, AvpCruisingStateType::LOCATING_2});
        state_switch_map_.insert({AvpCruisingStateType::PREPARED_4, AvpCruisingStateType::LOCATED_3});
        state_switch_map_.insert({AvpCruisingStateType::PREPARED_4, AvpCruisingStateType::CRUISING_5});

        state_switch_map_.insert({AvpCruisingStateType::CRUISING_5, AvpCruisingStateType::STANDBY_1});
        state_switch_map_.insert({AvpCruisingStateType::CRUISING_5, AvpCruisingStateType::PARKING_6});
        state_switch_map_.insert({AvpCruisingStateType::CRUISING_5, AvpCruisingStateType::OVERRIDE_7});
        state_switch_map_.insert({AvpCruisingStateType::CRUISING_5, AvpCruisingStateType::SUCCESS_8});
        state_switch_map_.insert({AvpCruisingStateType::CRUISING_5, AvpCruisingStateType::FAILED_9});
        state_switch_map_.insert({AvpCruisingStateType::CRUISING_5, AvpCruisingStateType::SUSPEND_10});
        state_switch_map_.insert({AvpCruisingStateType::CRUISING_5, AvpCruisingStateType::TERMINATE_11});

        state_switch_map_.insert({AvpCruisingStateType::PARKING_6, AvpCruisingStateType::STANDBY_1});
        state_switch_map_.insert({AvpCruisingStateType::PARKING_6, AvpCruisingStateType::SUCCESS_8});
        state_switch_map_.insert({AvpCruisingStateType::PARKING_6, AvpCruisingStateType::FAILED_9});
        state_switch_map_.insert({AvpCruisingStateType::PARKING_6, AvpCruisingStateType::SUSPEND_10});
        state_switch_map_.insert({AvpCruisingStateType::PARKING_6, AvpCruisingStateType::TERMINATE_11});

        state_switch_map_.insert({AvpCruisingStateType::OVERRIDE_7, AvpCruisingStateType::CRUISING_5});

        state_switch_map_.insert({AvpCruisingStateType::SUCCESS_8, AvpCruisingStateType::STANDBY_1});

        state_switch_map_.insert({AvpCruisingStateType::FAILED_9, AvpCruisingStateType::STANDBY_1});

        state_switch_map_.insert({AvpCruisingStateType::SUSPEND_10, AvpCruisingStateType::CRUISING_5});
        state_switch_map_.insert({AvpCruisingStateType::SUSPEND_10, AvpCruisingStateType::PARKING_6});
        state_switch_map_.insert({AvpCruisingStateType::SUSPEND_10, AvpCruisingStateType::TERMINATE_11});

        state_switch_map_.insert({AvpCruisingStateType::TERMINATE_11, AvpCruisingStateType::STANDBY_1});
    }
    void InitStatepolicyMap()
    {
        state_policy_map_[AvpCruisingStateType::IDLE_0] = std::bind(&AvpCruisingStateMachine::SwitchToIdle, this, std::placeholders::_1);
        state_policy_map_[AvpCruisingStateType::STANDBY_1] = std::bind(&AvpCruisingStateMachine::SwitchToStandby, this, std::placeholders::_1);
        state_policy_map_[AvpCruisingStateType::LOCATING_2] = std::bind(&AvpCruisingStateMachine::SwitchToLocating, this, std::placeholders::_1);
        state_policy_map_[AvpCruisingStateType::LOCATED_3] = std::bind(&AvpCruisingStateMachine::SwitchToLocated, this, std::placeholders::_1);
        state_policy_map_[AvpCruisingStateType::PREPARED_4] = std::bind(&AvpCruisingStateMachine::SwitchToPrepared, this, std::placeholders::_1);
        state_policy_map_[AvpCruisingStateType::CRUISING_5] = std::bind(&AvpCruisingStateMachine::SwitchToCruising, this, std::placeholders::_1);
        state_policy_map_[AvpCruisingStateType::PARKING_6] = std::bind(&AvpCruisingStateMachine::SwitchToParking, this, std::placeholders::_1);
        state_policy_map_[AvpCruisingStateType::OVERRIDE_7] = std::bind(&AvpCruisingStateMachine::SwitchToOverride, this, std::placeholders::_1);
        state_policy_map_[AvpCruisingStateType::SUCCESS_8] = std::bind(&AvpCruisingStateMachine::SwitchToSuccess, this, std::placeholders::_1);
        state_policy_map_[AvpCruisingStateType::FAILED_9] = std::bind(&AvpCruisingStateMachine::SwitchToFailed, this, std::placeholders::_1);
        state_policy_map_[AvpCruisingStateType::SUSPEND_10] = std::bind(&AvpCruisingStateMachine::SwitchToSuspend, this, std::placeholders::_1);
        state_policy_map_[AvpCruisingStateType::TERMINATE_11] = std::bind(&AvpCruisingStateMachine::SwitchToTerminate, this, std::placeholders::_1);
    }
    AvpCruisingStateType CalcCrntState() const noexcept override
    {
        AvpCruisingStateType crnt_state = GetCrntState();
        auto to_state_list = state_switch_map_.equal_range(crnt_state);
        std::cout << "111" << std::endl;
        std::for_each(to_state_list.first, to_state_list.second, [this, &crnt_state](auto state){
            std::cout << "222" << std::endl;
            auto tmp_crnt_state = state.first;
            auto to_switch_state = state.second;
            if (state_policy_map_.find(to_switch_state) != std::end(state_policy_map_))
            {
                std::cout << "333" << std::endl;
                if (state_policy_map_.at(to_switch_state)(tmp_crnt_state))
                {
                    std::cout << "func" << std::endl;
                    crnt_state = to_switch_state;
                    return crnt_state;
                }
            }
            else 
            {   
                std::cout << "444" << std::endl;
                std::cout << "Invalid to-switch state : " << static_cast<uint32_t>(state.second) << std::endl;
                return crnt_state;
            }
        });
        return crnt_state;
    }
public:
    void Run() override
    {
        uint32_t count = 20;
        while (GetInitFlag())
        {  
            // auto state = CalcCrntState();
            // std::cout << "crnt state : " << static_cast<uint32_t>(state) << std::endl;
            UpdateState(static_cast<AvpCruisingStateType>(10 - count / 2));
            PrintData();

            // std::cout << "[Avp] Crnt State : " << AvpFormator(avp_cruising_str_map.at(GetCrntState())) 
            // << ", Last State : " << AvpFormator(avp_cruising_str_map.at(GetLastState()))
            // << ", Prvs State : " << AvpFormator(avp_cruising_str_map.at(GetPrvsState())) 
            // << ", Duration : " << GetDuration().count() << "(S)" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (count == 0)
            {
                break;
            }
            else
            {
                count--;
            }
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