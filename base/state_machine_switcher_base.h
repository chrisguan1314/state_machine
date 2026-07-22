#pragma once

#include "state_machine_param_base.h"
#include "state_machine_inputer_base.h"
#include "state_machine_outputer_base.h"

#include <type_traits>
#include <atomic>
#include <chrono>

// 类模板的模板声明（the declaration of class template, including 1 default template argument）
template <typename T, typename = typename std::enable_if_t<std::is_enum_v<T>>>
class StateMachineSwticherBase;

template <typename T, typename>
class StateMachineSwticherBase
{
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
    uint32_t freq_{20};
public:
    virtual void Init() = 0; 
    virtual void PrintStateSwitchInfo() = 0;
    virtual T CalcNextState(std::shared_ptr<StateMachineParamBase> param, std::shared_ptr<StateMachineInputerBase> input) = 0;  
public:
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
    void UpdateState(std::shared_ptr<StateMachineParamBase> param, std::shared_ptr<StateMachineInputerBase> input)
    {
        UpdateState(CalcNextState(param, input));
    }
public:
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
    bool IsStateChanged() const noexcept
    {
        return crnt_state_.load() != last_state_.load();
    }
public:
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