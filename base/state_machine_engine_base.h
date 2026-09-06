#pragma once

#include "state_machine_param_base.h"
#include "state_machine_inputer_base.h"
#include "state_machine_switcher_base.h"
#include "state_machine_outputer_base.h"

#include <string>
#include <thread>
#include <atomic>
#include <iostream>
#include <stdexcept>

template <typename State, typename Param, typename Inputer, typename Switcher, typename Outputer, 
typename = typename std::enable_if_t<std::is_enum_v<State>>,
// 类模板的模板声明（the declaration of class template, including 1 default template argument）
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineParamBase, Param>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineInputerBase, Inputer>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineSwitcherBase<State>, Switcher>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineOutputerBase<State, Param, Inputer, Switcher>, Outputer>>>
class StateMachineEngineBase;

// 在定义类模板时，不再需要指定默认模板参数
// don't need to specify that default template argument when define the class template 
template <typename State, typename Param, typename Inputer, typename Switcher, typename Outputer, typename, typename, typename, typename, typename>
class StateMachineEngineBase
{
public:
    using StateType = State;
    using ParamType = Param;
    using InputerType = Inputer;
    using SwitcherType = Switcher;
    using OutputerType = Outputer;
    using ParamPtr = std::shared_ptr<ParamType>;
    using InputerSPtr = std::shared_ptr<InputerType>;
    using SwitcherSPtr = std::shared_ptr<SwitcherType>;
    using OutputerSPtr = std::shared_ptr<OutputerType>;
private:
    std::string name_;
    uint32_t freq_{20};
    std::atomic_bool init_flag_{false};
    std::atomic_bool run_flag_{false};
    ParamPtr param_sptr_{std::make_shared<ParamType>()};
    InputerSPtr input_sptr_{std::make_shared<InputerType>()};
    SwitcherSPtr switch_sptr_{std::make_shared<SwitcherType>()};
    OutputerSPtr output_sptr_{std::make_shared<OutputerType>()};
    std::unique_ptr<std::thread> thrd_uptr_{nullptr};
protected:
    StateMachineEngineBase(std::string name, uint32_t freq = 20) : name_(name), freq_{freq}
    {
        if (name_.empty())
        {
            name_ = "StateMachineEngineBase";
        }
        if (!param_sptr_)
        {
            throw std::invalid_argument("StateMachineEngineBase: param_sptr_ is nullptr");
        }
        if (!input_sptr_)
        {
            throw std::invalid_argument("StateMachineEngineBase: input_sptr_ is nullptr");
        }
        if (!switch_sptr_)
        {
            throw std::invalid_argument("StateMachineEngineBase: switch_sptr_ is nullptr");
        }
        if (!output_sptr_)
        {
            throw std::invalid_argument("StateMachineEngineBase: output_sptr_ is nullptr");
        }
        std::cout << "\n[StateMachine] ***************************************\n" << std::endl;
        std::cout << "[StateMachine] StateMachineEngineBase: " << name_ << " is Created, Frequency : " << freq_ << std::endl;
    }
    ~StateMachineEngineBase()
    {
        if (thrd_uptr_ && thrd_uptr_->joinable())
        {
            thrd_uptr_->join();
        }
        Stop();
    }
public:
    void Init() 
    {
        param_sptr_->Init();
        input_sptr_->Init();;
        switch_sptr_->Init();
        output_sptr_->Init();

        SetInitFlag(true);

        thrd_uptr_ = std::make_unique<std::thread>(&StateMachineEngineBase::Run, this);
    }
    void Start()
    {
        if (GetInitFlag())
        {
            SetRunFlag(true);
        }
        else
        {
            std::cout << "StateMachineEngineBase::Start() failed, please call Init() first!" << std::endl;
        }
    }
    void Stop()
    {
        SetRunFlag(false);
        SetInitFlag(false);
    }
    void Run()
    {
        while (GetInitFlag())
        {
            auto start_time = steady_clock::now();
            if (GetRunFlag())
            {
                param_sptr_->UpdateParam();
                input_sptr_->UpdateEvent();
                switch_sptr_->UpdateState();
                output_sptr_->UpdateAction(param_sptr_, input_sptr_, switch_sptr_);
            }
            auto elapsed_time = duration_cast<milliseconds>(steady_clock::now() - start_time).count();
            if (elapsed_time < (1000 / freq_))  
            {
                std::this_thread::sleep_for(milliseconds((1000 / freq_) - elapsed_time));
            }
            else
            {
                std::cout << "StateMachineEngineBase::Run() is running slower than expected, elapsed time: " << elapsed_time << " ms" << std::endl;
            }
        }
    }
private:
    bool GetInitFlag() const noexcept
    {
        return init_flag_.load();
    }
    void SetInitFlag(bool flag = false) noexcept
    {
        init_flag_.store(flag);
    }
    bool GetRunFlag() const noexcept
    {
        return run_flag_.load();
    }
    void SetRunFlag(bool flag = false) noexcept
    {
        run_flag_.store(flag);
    }
    uint32_t GetFrequency() const noexcept
    {
        return freq_;
    }
    void  SetFrequency(uint32_t freq = 20) noexcept
    {
        freq_ = freq;
    }
};