#pragma once

#include "state_machine_param_base.h"
#include "state_machine_inputer_base.h"

#include <type_traits>
#include <chrono>

using namespace std::chrono;

template <typename T1, typename T2>
using is_decay_same = typename std::is_same<std::decay_t<T1>, std::decay_t<T2>>::type;

template <typename State>
class SystemModeInfo
{
public:
    using StateType = State;
public:
    SystemModeInfo() noexcept = default;
private:
    StateType crnt_state_{};
    StateType last_state_{};
    StateType prvs_state_{};
    uint32_t count_{0};
    system_clock::time_point system_start_time_{system_clock::now()};
    steady_clock::time_point steady_start_time_{steady_clock::now()};
    seconds duration_{0}; 
public:
    const StateType GetCrntState() const noexcept
    {
        return crnt_state_;
    }
    const StateType GetLastState() const noexcept
    {
        return last_state_;
    }
    const StateType GetPrvsState() const noexcept
    {
        return prvs_state_;
    }
    const uint32_t GetCount() const noexcept
    {
        return count_;
    }
    const system_clock::time_point& GetStartSystemTime() const noexcept
    {
        return system_start_time_;
    }
    const steady_clock::time_point& GetStartSteadyTime() const noexcept
    {
        return steady_start_time_;
    }
    const seconds& GetDuration() const noexcept
    {
        return duration_;
    }
public:
    bool IsStateChanged() const noexcept
    {
        return crnt_state_ != last_state_;
    }
public:
    void SetCrntState(StateType state = StateType{}) noexcept
    {
        crnt_state_ = state;
    }
    void SetLastState(StateType state = StateType{}) noexcept
    {
        last_state_ = state;
    }
    void SetPrvsState(StateType state = StateType{}) noexcept
    {
        prvs_state_ = state;
    }
    void SetCount(uint32_t count = 0) noexcept
    {
        count_ = count;
    }
    template <typename TimePoint, typename = typename std::enable_if_t<is_decay_same<TimePoint, system_clock::time_point>::value>>
    void SetStartSystemTime(TimePoint && time_point) noexcept
    {
        system_start_time_ = std::forward<TimePoint>(time_point);
    }
    template <typename TimePoint, typename = typename std::enable_if_t<is_decay_same<TimePoint, steady_clock::time_point>::value>>
    void SetStartSteadyTime(TimePoint && time_point) noexcept
    {
        steady_start_time_ = std::forward<TimePoint>(time_point);
    }
    template <typename Duration, typename = typename std::enable_if_t<is_decay_same<Duration, seconds>::value>>
    void SetDuration(Duration && duration) noexcept
    {
        duration_ = std::forward<Duration>(duration);
    }
};