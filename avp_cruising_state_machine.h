#pragma once

#include "avp_cruising_input.h"
#include "avp_cruising_output.h"
#include "avp_cruising_param.h"
#include "state_machine_base.h"
#include "log_base.h"
#include "str_map.h"

#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <algorithm>

const std::string AvpFormat(const std::string& str)
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
            std::cout << "[Avp] Crnt State : " << AvpFormat(avp_cruising_str_map.at(base.GetCrntState())) 
                << ", Last State : " << AvpFormat(avp_cruising_str_map.at(base.GetLastState()))
                << ", Prvs State : " << AvpFormat(avp_cruising_str_map.at(base.GetPrvsState())) 
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
private:
    AvpCruisingStateMachine(LogPrintFunc<AvpCruisingStateType> func = AvpCruisingPrinter()) : StateMachineBase("AvpCruising", func)
    {
        SetEnableFlag(true);
    }
    AvpCruisingStateMachine(const AvpCruisingStateMachine&) = delete;
    AvpCruisingStateMachine& operator=(const AvpCruisingStateMachine&) = delete;
public:
    ~AvpCruisingStateMachine()
    {
        SetSetupFlag(false);
    }
public:
    void Run() override
    {
        uint32_t count = 20;
        while (GetInitFlag())
        {  
            UpdateState(static_cast<AvpCruisingStateType>(10 - count / 2));
            PrintData();
            // std::cout << "[Avp] Crnt State : " << AvpFormat(avp_cruising_str_map.at(GetCrntState())) 
            // << ", Last State : " << AvpFormat(avp_cruising_str_map.at(GetLastState()))
            // << ", Prvs State : " << AvpFormat(avp_cruising_str_map.at(GetPrvsState())) 
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