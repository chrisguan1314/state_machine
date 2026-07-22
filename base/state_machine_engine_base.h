#pragma once

#include "state_machine_param_base.h"
#include "state_machine_inputer_base.h"
#include "state_machine_switcher_base.h"
#include "state_machine_outputer_base.h"

#include <type_traits>
#include <string>
#include <thread>
#include <memory>
#include <atomic>

// 类模板的模板声明（the declaration of class template, including 1 default template argument）
template <typename State, typename Param, typename Inputer, typename Switcher, typename Outputer, typename = typename std::enable_if_t<std::is_enum_v<State>>>
class StateMachineEngineBase;

// 在定义类模板时，不再需要指定默认模板参数
// don't need to specify that default template argument when define the class template 
template <typename State, typename Param, typename Inputer, typename Switcher, typename Outputer, typename>
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
    std::atomic_bool init_flag_{false};
    // the frequency of print log
    uint32_t freq_{20};
    std::string name_;
    ParamPtr param_sptr_{nullptr};
    InputerSPtr input_sptr_{nullptr};
    SwitcherSPtr switch_sptr_{nullptr};
    OutputerSPtr output_sptr_{nullptr};
    std::unique_ptr<std::thread> thrd_uptr_{nullptr};
protected:
    StateMachineEngineBase(std::string name, ParamPtr && param, InputerSPtr && input, SwitcherSPtr && switcher, OutputerSPtr && output) :
    name_(name),
    param_sptr_{param},
    input_sptr_{input},
    switch_sptr_{switcher}, 
    output_sptr_{output}
    {
    
    }
    ~StateMachineEngineBase()
    {
        if (thrd_uptr_ && thrd_uptr_->joinable())
        {
            thrd_uptr_->join();
        }
    }
public:
    void Init() 
    {
        param_sptr_->Init();
        input_sptr_->Init();;
        switch_sptr_->Init();
        output_sptr_->Init();

        thrd_uptr_ = std::make_unique<std::thread>(&StateMachineEngineBase::Run, this);
        
        SetInitFlag(true);
    }
    void Run()
    {
        while (true)
        {
            if (GetInitFlag())
            {
                param_sptr_->UpdateParam();
                input_sptr_->UpdateEvent(param_sptr_);
                switch_sptr_->UpdateState(param_sptr_, input_sptr_);
                output_sptr_->UpdateAction(param_sptr_, input_sptr_, switch_sptr_);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / freq_));
        }
    }
protected:
    void SetInitFlag(bool flag = false) noexcept
    {
        init_flag_.store(flag);
    }
    bool GetInitFlag() const noexcept
    {
        return init_flag_.load();
    }
};