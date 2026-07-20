#pragma once

#include "state_machine_param_base.h"
#include "state_machine_input_base.h"
#include "state_machine_switch_base.h"
#include "state_machine_output_base.h"

#include <iostream>
#include <chrono>
#include <type_traits>
#include <iomanip>
#include <string>
#include <thread>
#include <memory>
#include <atomic>
#include <functional>

// 类模板的模板声明（the declaration of class template, including 1 default template argument）
template <typename T, typename = typename std::enable_if_t<std::is_enum_v<T>>>
class StateMachineBase;

// alias declaration by using of class template 
template <typename T>
using PrinterType = std::function<void(const StateMachineBase<T>&)>;

// 在定义类模板时，不再需要指定默认模板参数
// don't need to specify that default template argument when define the class template 
template <typename T, typename>
class StateMachineBase
{
public:
    struct DefaultPrinter
    {
        virtual void operator()(const StateMachineBase& base) const
        {
            std::cout << "Crnt State : " << static_cast<uint32_t>(base.GetCrntState()) 
                << ", Last State : " << static_cast<uint32_t>(base.GetLastState())
                << ", Prvs State : " << static_cast<uint32_t>(base.GetPrvsState())
                << ", Duration : " << base.GetDuration().count() << "(S)" << std::endl; 
        }
    };
public:
    using system_time_point = std::chrono::system_clock::time_point;
    using steady_time_point = std::chrono::steady_clock::time_point;
    using duration_of_second = std::chrono::duration<uint32_t>;
    template <typename _T1, typename _T2>
    using is_decay_same = typename std::is_same<std::decay_t<_T1>, _T2>::type;
    using atomic_T = std::atomic<T>;
private:
    atomic_T crnt_state_{static_cast<T>(0)};
    atomic_T last_state_{static_cast<T>(0)};
    atomic_T prvs_state_{static_cast<T>(0)};
    uint32_t count_{0};
    system_time_point system_start_time_{std::chrono::system_clock::now()};
    steady_time_point steady_start_time_{std::chrono::steady_clock::now()};
    duration_of_second duration_{0}; 
    std::unique_ptr<PrinterType<T>> func_{nullptr};
    // 整体的这里的标志位都应该用原子变量，以避免可能带来的数据竞争

    // 其实这个使能标志位应该是由调度器来加载相关参数的
    // 根据加载的结果来决定是否生成该状态机对象
    std::atomic_bool enable_flag_{false};
    // 如果功能开关打开，则对该状态机进行初始化
    // 初始化大概分为参数加载和通信协议适配
    std::atomic_bool init_flag_{false};
    // 当初始化完成之后，我们就可以创建线程开始工作了
    std::atomic_bool setup_flag_{false};
    // the frequency of print log
    uint32_t freq_{20};

    std::shared_ptr<StateMachineParamBase> param_sptr_{nullptr};
    std::shared_ptr<StateMachineInputBase> input_sptr_{nullptr};
    std::shared_ptr<StateMachineSwtichBase<T>> switch_sptr_{nullptr};
    std::shared_ptr<StateMachineOutputBase> output_sptr_{nullptr};
    std::unique_ptr<std::thread> thrd_uptr_{nullptr};
    std::string name_;
protected:
    StateMachineBase(std::string name) : 
    name_(name),
    param_sptr_{std::make_shared<StateMachineParamBase>()},
    input_sptr_{std::make_shared<StateMachineInputBase>()},
    switch_sptr_{std::make_shared<StateMachineSwtichBase<T>>()}, 
    output_sptr_{std::make_shared<StateMachineOutputBase>()}
    {
        
    }
    StateMachineBase(std::string name, std::shared_ptr<StateMachineParamBase> && param, std::shared_ptr<StateMachineInputBase> && input, std::shared_ptr<StateMachineSwtichBase<T>> && switches, std::shared_ptr<StateMachineOutputBase> && output) :
    name_(name),
    param_sptr_{param},
    input_sptr_{input},
    switch_sptr_{switches}, 
    output_sptr_{output}
    {
        auto now = std::chrono::system_clock::to_time_t(system_start_time_);
        std::cout << "Construct a " << name + "StateMachine" << " object, at " 
                  << std::put_time(std::localtime(&now), "%F %T") << std::endl;
        Init();
    }
    ~StateMachineBase()
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

        thrd_uptr_ = std::make_unique<std::thread>(&StateMachineBase::Run, this);
    }
    void Run()
    {
        while (true)
        {
            param_sptr_->UpdateParam();
            input_sptr_->UpdateEvent();
            switch_sptr_->UpdateState(input_sptr_);
            // UpdateState();
            output_sptr_->UpdateAction();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    
    void PrintData() const
    {
        if (IsStateChanged())
        {
            (*func_)(*this);
        }
        else if (GetCount() % GetFrequency() * 5 == 0)
        {
            (*func_)(*this);
        }
    }
    void PrintInfo()
    {
        if (IsStateChanged())
        {
            PrintStateSwitchInfo();
        }
        else if (GetCount() % GetFrequency() * 5 == 0)
        {
            PrintStateSwitchInfo();
        }
    }
    virtual void PrintStateSwitchInfo()
    {
        std::cout << "555" << std::endl;
    }
public:
    void UpdateState() noexcept
    {
        UpdateState(CalcNextState());
    }
    void UpdateState(T state) noexcept
    {
        if (crnt_state_.load() != state)
        {
            SetPrvsState(crnt_state_.load());
            SetCount();
            SetStartSystemTime(std::chrono::system_clock::now());
            SetStartSteadyTime(std::chrono::steady_clock::now());
            SetDuration(duration_of_second(0U));
        }
        SetLastState(crnt_state_.load());
        SetCrntState(state);
        SetCount(GetCount() + 1);
        SetDuration(std::chrono::duration_cast<duration_of_second>(std::chrono::steady_clock::now() - steady_start_time_));
        PrintInfo();
    }
    const T GetCrntState() const noexcept
    {
        return crnt_state_.load();
    }
    const T GetLastState() const noexcept
    {
        return last_state_.load();
    }
    const T GetPrvsState() const noexcept
    {
        return prvs_state_.load();
    }
    const uint32_t GetCount() const noexcept
    {
        return count_;
    }
    const system_time_point& GetStartSystemTime() const noexcept
    {
        return system_start_time_;
    }
    const steady_time_point& GetStartSteadyTime() const noexcept
    {
        return steady_start_time_;
    }
    const duration_of_second& GetDuration() const noexcept
    {
        return duration_;
    }
    uint32_t GetFrequency() const noexcept
    {
        return freq_;
    }
public:
    virtual T CalcNextState() const noexcept 
    {
        return static_cast<T>(0);
    }
protected:
    void SetEnableFlag(bool flag = false) noexcept
    {
        enable_flag_.store(flag);
    }
    void SetInitFlag(bool flag = false) noexcept
    {
        init_flag_.store(flag);
    }
    void SetSetupFlag(bool flag = false) noexcept
    {
        setup_flag_.store(flag);
    }
    bool GetEnableFlag() const noexcept
    {
        return enable_flag_.load();
    }
    bool GetInitFlag() const noexcept
    {
        return init_flag_.load();
    }
    bool GetSetupFlag() const noexcept
    {
        return setup_flag_.load();
    }
public:
    bool IsStateChanged() const noexcept
    {
        return crnt_state_.load() != last_state_.load();
    }
private:
    void SetCrntState(T state = static_cast<T>(0)) noexcept
    {
        crnt_state_.store(state);
    }
    void SetLastState(T state = static_cast<T>(0)) noexcept
    {
        last_state_.store(state);
    }
    void SetPrvsState(T state = static_cast<T>(0)) noexcept
    {
        prvs_state_.store(state);
    }
    void SetCount(uint32_t count = 0) noexcept
    {
        count_ = count;
        std::cout << "count : " << count_ << std::endl;
    }
    template <typename TimePoint, typename = typename std::enable_if_t<is_decay_same<TimePoint, system_time_point>::value>>
    void SetStartSystemTime(TimePoint && time_point) noexcept
    {
        system_start_time_ = std::forward<TimePoint>(time_point);
    }
    template <typename TimePoint, typename = typename std::enable_if_t<is_decay_same<TimePoint, steady_time_point>::value>>
    void SetStartSteadyTime(TimePoint && time_point) noexcept
    {
        steady_start_time_ = std::forward<TimePoint>(time_point);
    }
    template <typename Duration, typename = typename std::enable_if_t<is_decay_same<Duration, duration_of_second>::value>>
    void SetDuration(Duration && duration) noexcept
    {
        duration_ = std::forward<Duration>(duration);
    }
};