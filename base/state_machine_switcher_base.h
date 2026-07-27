#pragma once

#include "concept_base.h"
#include "state_machine_param_base.h"
#include "state_machine_inputer_base.h"

#include <type_traits>
#include <atomic>
#include <chrono>

using namespace std::chrono;

template <typename T1, typename T2>
using is_decay_same = typename std::is_same<std::decay_t<T1>, std::decay_t<T2>>::type;


#if __cplusplus >= 202002L
template <is_enum State, is_param_base Param, is_inputer_base<Param> Inputer>
#else
template <typename State, typename Param, typename Inputer,
          typename = typename std::enable_if_t<std::is_enum_v<State>>,
          typename = typename std::enable_if_t<std::is_base_of_v<StateMachineParamBase, Param>>,
          typename = typename std::enable_if_t<std::is_base_of_v<StateMachineInputerBase<Param>, Inputer>>>
#endif
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
    atomic_T crnt_state_{static_cast<StateType>(0)};
    atomic_T last_state_{static_cast<StateType>(0)};
    atomic_T prvs_state_{static_cast<StateType>(0)};
    uint32_t count_{0};
    system_clock::time_point system_start_time_{system_clock::now()};
    steady_clock::time_point steady_start_time_{steady_clock::now()};
    seconds duration_{0}; 
    uint32_t freq_{20};
public:
    virtual void Init() = 0; 
    virtual void PrintStateSwitchInfo() const = 0;
    virtual StateType CalcNextState(ParamSPtr param, InputerSPtr input) = 0;
public:
    void PrintInfo() const
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
    void UpdateState(StateType state) noexcept
    {
        if (crnt_state_.load() != state)
        {
            SetPrvsState(crnt_state_.load());
            SetCount();
            SetStartSystemTime(system_clock::now());
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
    const StateType GetCrntState() const noexcept
    {
        return crnt_state_.load();
    }
    const StateType GetLastState() const noexcept
    {
        return last_state_.load();
    }
    const StateType GetPrvsState() const noexcept
    {
        return prvs_state_.load();
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
    void SetCrntState(StateType state = static_cast<StateType>(0)) noexcept
    {
        crnt_state_.store(state);
    }
    void SetLastState(StateType state = static_cast<StateType>(0)) noexcept
    {
        last_state_.store(state);
    }
    void SetPrvsState(StateType state = static_cast<StateType>(0)) noexcept
    {
        prvs_state_.store(state);
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

#if __cplusplus >= 202002L
template <typename T, typename State, typename Param, typename Inputer>
concept is_switcher_base = 
    is_enum<State> &&
    is_param_base<Param> && 
    is_inputer_base<Inputer, Param> && 
    std::derived_from<T, StateMachineSwitcherBase<typename T::StateType, Param, Inputer>>;
#endif