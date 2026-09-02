#pragma once

#include "state_machine_param_base.h"
#include "state_machine_inputer_base.h"

#include <type_traits>
#include <chrono>

using namespace std::chrono;

template <typename T1, typename T2>
using is_decay_same = typename std::is_same<std::decay_t<T1>, std::decay_t<T2>>::type;

template <typename Mode>
class SystemModeInfo
{
public:
    using ModeType = Mode;
public:
    SystemModeInfo() noexcept = default;
private:
    ModeType crnt_{};
    ModeType last_{};
    ModeType prvs_{};
    uint32_t count_{0};
    steady_clock::time_point start_time_{steady_clock::now()};
    seconds duration_{0}; 
public:
    void Update(ModeType mode)
    {
        if (mode != crnt_)
        {
            prvs_ = crnt_;
            count_ = 0;
            start_time_ = steady_clock::now();
        }
        else
        {
            ++count_;
            duration_ = duration_cast<seconds>(steady_clock::now() - start_time_);
        }
        last_ = crnt_;
        crnt_ = mode;
    }
    const ModeType GetCrnt() const noexcept
    {
        return crnt_;
    }
    const ModeType GetLast() const noexcept
    {
        return last_;
    }
    const ModeType GetPrvs() const noexcept
    {
        return prvs_;
    }
    const uint32_t GetCount() const noexcept
    {
        return count_;
    }
    const steady_clock::time_point& GetSteadyTime() const noexcept
    {
        return start_time_;
    }
    const seconds& GetDuration() const noexcept
    {
        return duration_;
    }
public:
    bool IsChanged() const noexcept
    {
        return crnt_ != last_;
    }
public:
    void SetCrnt(ModeType state = ModeType{}) noexcept
    {
        crnt_ = state;
    }
    void SetLast(ModeType state = ModeType{}) noexcept
    {
        last_ = state;
    }
    void SetPrvs(ModeType state = ModeType{}) noexcept
    {
        prvs_ = state;
    }
    void SetCount(uint32_t count = 0) noexcept
    {
        count_ = count;
    }
    template <typename TimePoint, typename = typename std::enable_if_t<is_decay_same<TimePoint, steady_clock::time_point>::value>>
    void SetStartTime(TimePoint && time_point) noexcept
    {
        start_time_ = std::forward<TimePoint>(time_point);
    }
    template <typename Duration, typename = typename std::enable_if_t<is_decay_same<Duration, seconds>::value>>
    void SetDuration(Duration && duration) noexcept
    {
        duration_ = std::forward<Duration>(duration);
    }
};