#pragma once

#include "state_machine_param_base.h"
#include "state_machine_inputer_base.h"

#include <chrono>
#include <cstdint>
#include <shared_mutex>
#include <type_traits>

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
    SystemModeInfo(const SystemModeInfo &other)
    {
        std::shared_lock<std::shared_mutex> lck(other.mtx_);
        CopyFrom(other);
    }

    SystemModeInfo &operator=(const SystemModeInfo &other)
    {
        if (this != &other)
        {
            // 这里scoped_lock没有shared_lock的功能
            std::scoped_lock lck(mtx_, other.mtx_);
            CopyFrom(other);
        }
        return *this;
    }
private:
    void CopyFrom(const SystemModeInfo &other) noexcept
    {
        crnt_ = other.crnt_;
        last_ = other.last_;
        prvs_ = other.prvs_;
        count_ = other.count_;
        start_time_ = other.start_time_;
        duration_ = other.duration_;
    }

private:
    mutable std::shared_mutex mtx_;
    ModeType crnt_{static_cast<ModeType>(0)};
    ModeType last_{static_cast<ModeType>(0)};
    ModeType prvs_{static_cast<ModeType>(0)};
    uint32_t count_{0};
    steady_clock::time_point start_time_{steady_clock::now()};
    seconds duration_{0}; 
public:
    void Update(ModeType mode)
    {
        std::lock_guard<std::shared_mutex> lck(mtx_);
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
    ModeType GetCrnt() const noexcept   
    {
        std::shared_lock<std::shared_mutex> lck(mtx_);
        return crnt_;
    }
    ModeType GetLast() const noexcept
    {
        std::shared_lock<std::shared_mutex> lck(mtx_);
        return last_;
    }
    ModeType GetPrvs() const noexcept
    {
        std::shared_lock<std::shared_mutex> lck(mtx_);
        return prvs_;
    }
    uint32_t GetCount() const noexcept
    {
        std::shared_lock<std::shared_mutex> lck(mtx_);
        return count_;
    }
    steady_clock::time_point GetSteadyTime() const noexcept
    {
        std::shared_lock<std::shared_mutex> lck(mtx_);
        return start_time_;
    }
    seconds GetDuration() const noexcept
    {
        std::shared_lock<std::shared_mutex> lck(mtx_);
        return duration_;
    }
public:
    bool IsChanged() const noexcept
    {
        std::shared_lock<std::shared_mutex> lck(mtx_);
        return crnt_ != last_;
    }
    bool IsChangeTo(ModeType mode) const noexcept
    {
        std::shared_lock<std::shared_mutex> lck(mtx_);
        return crnt_ == mode && crnt_ != last_;
    }
public:
    void SetCrnt(ModeType state = ModeType{})
    {
        std::lock_guard<std::shared_mutex> lck(mtx_);
        crnt_ = state;
    }
    void SetLast(ModeType state = ModeType{})
    {
        std::lock_guard<std::shared_mutex> lck(mtx_);
        last_ = state;
    }
    void SetPrvs(ModeType state = ModeType{})
    {
        std::lock_guard<std::shared_mutex> lck(mtx_);
        prvs_ = state;
    }
    void SetCount(uint32_t count = 0)
    {
        std::lock_guard<std::shared_mutex> lck(mtx_);
        count_ = count;
    }
    template <typename TimePoint, typename = typename std::enable_if_t<is_decay_same<TimePoint, steady_clock::time_point>::value>>
    void SetStartTime(TimePoint && time_point)
    {
        std::lock_guard<std::shared_mutex> lck(mtx_);
        start_time_ = std::forward<TimePoint>(time_point);
    }
    template <typename Duration, typename = typename std::enable_if_t<is_decay_same<Duration, seconds>::value>>
    void SetDuration(Duration && duration)
    {
        std::lock_guard<std::shared_mutex> lck(mtx_);
        duration_ = std::forward<Duration>(duration);
    }
};