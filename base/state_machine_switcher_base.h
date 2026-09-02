#pragma once

#include "state_machine_param_base.h"
#include "state_machine_inputer_base.h"

#include <type_traits>
#include <atomic>
#include <chrono>

// 类模板的模板声明（the declaration of class template, including 1 default template argument）
template <typename State, typename Param, typename Inputer, 
typename = typename std::enable_if_t<std::is_enum_v<State>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineParamBase, Param>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineInputerBase<Param>, Inputer>>>
class StateMachineSwitcherBase;

using namespace std::chrono;

template <typename T1, typename T2>
using is_decay_same = typename std::is_same<std::decay_t<T1>, std::decay_t<T2>>::type;

template <typename State, typename Param, typename Inputer, typename, typename, typename>
class StateMachineSwitcherBase
{
public:
    using StateType = State;
    using ParamType = Param;
    using InputerType = Inputer;
    using ParamSPtr = std::shared_ptr<ParamType>;
    using InputerSPtr = std::shared_ptr<InputerType>;
    using atomic_T = std::atomic<StateType>;
public:
    StateMachineSwitcherBase() noexcept = default;
private:
    inline static atomic_T crnt_state_{static_cast<StateType>(0)};
    inline static atomic_T last_state_{static_cast<StateType>(0)};
    inline static atomic_T prvs_state_{static_cast<StateType>(0)};
    inline static uint32_t count_{0};
    inline static steady_clock::time_point steady_start_time_{steady_clock::now()};
    inline static seconds duration_{0};
    uint32_t freq_{20};
public:
    virtual void Init() = 0; 
    virtual void PrintStateSwitchInfo() = 0;
    virtual StateType CalcNextState(ParamSPtr param, InputerSPtr input) = 0;
public:
    void PrintInfo()
    {
        if (IsStateChanged())
        {
            PrintStateSwitchInfo();
        }
        else 
        {
            if (crnt_state_ >= static_cast<StateType>(2))
            {
                if (GetCount() % GetFrequency() * 5 == 0)
                {
                    PrintStateSwitchInfo(); 
                }
            }
        }
    }
    void UpdateState(StateType state) noexcept
    {
        if (crnt_state_.load() != state)
        {
            SetPrvsState(crnt_state_.load());
            SetCount();
            SetStartSteadyTime(steady_clock::now());
            SetDuration(seconds(0U));
        }
        SetLastState(crnt_state_.load());
        SetCrntState(state);
        SetCount(GetCount() + 1);
        SetDuration(duration_cast<seconds>(steady_clock::now() - steady_start_time_));
        PrintInfo();
    }
    void UpdateState(ParamSPtr param, InputerSPtr input)
    {
        UpdateState(CalcNextState(param, input));
    }
public:
    static StateType GetCrntState() noexcept
    {
        return crnt_state_.load();
    }
    static StateType GetLastState() noexcept
    {
        return last_state_.load();
    }
    static StateType GetPrvsState() noexcept
    {
        return prvs_state_.load();
    }
    static uint32_t GetCount() noexcept
    {
        return count_;
    }
    static const steady_clock::time_point& GetStartSteadyTime() noexcept
    {
        return steady_start_time_;
    }
    static const seconds& GetDuration() noexcept
    {
        return duration_;
    }
private:
    uint32_t GetFrequency() noexcept
    {
        return freq_;
    }
public:
    static bool IsStateChanged() noexcept
    {
        return crnt_state_.load() != last_state_.load();
    }
public:
    static void SetCrntState(StateType state = static_cast<StateType>(0)) noexcept
    {
        crnt_state_.store(state);
    }
    static void SetLastState(StateType state = static_cast<StateType>(0)) noexcept
    {
        last_state_.store(state);
    }
    static void SetPrvsState(StateType state = static_cast<StateType>(0)) noexcept
    {
        prvs_state_.store(state);
    }
    static void SetCount(uint32_t count = 0) noexcept
    {
        count_ = count;
    }
    template <typename TimePoint, typename = typename std::enable_if_t<is_decay_same<TimePoint, steady_clock::time_point>::value>>
    static void SetStartSteadyTime(TimePoint && time_point) noexcept
    {
        steady_start_time_ = std::forward<TimePoint>(time_point);
    }
    template <typename Duration, typename = typename std::enable_if_t<is_decay_same<Duration, seconds>::value>>
    static void SetDuration(Duration && duration) noexcept
    {
        duration_ = std::forward<Duration>(duration);
    }
};