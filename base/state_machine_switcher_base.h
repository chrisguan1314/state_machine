#pragma once

#include "state_machine_param_base.h"
#include "state_machine_inputer_base.h"
#include "state_switch_table.h"
#include "enum.h"

#include <type_traits>
#include <atomic>
#include <chrono>
#include <mutex>

using namespace std::chrono;

template <typename T1, typename T2>
using is_decay_same = typename std::is_same<std::decay_t<T1>, std::decay_t<T2>>::type;

/**
 * @brief 为枚举状态机提供转换计算和状态上下文管理。
 *
 * 派生类在 Init() 中为每个源状态登记候选目标状态及其转换条件，并在
 * PrintStateInfo() 中实现诊断输出。调用无参 UpdateState() 时，本类按登记顺序
 * 执行条件判断，并切换到首个条件成立的目标状态；没有条件成立时保持当前状态。
 *
 * 每次更新都会维护当前、上一和前序状态，以及当前状态的周期计数和持续时间；
 * 状态变化或满足周期条件时会触发诊断输出。当前、上一、前序状态、功能开启类型
 * 和激活类型按 State 模板实参共享，因此使用相同状态枚举的多个切换器实例会共享
 * 这些状态上下文。转换表和诊断输出频率则由各实例独立持有。
 *
 * @tparam State 状态枚举类型，必须为枚举。
 * @note 调用 UpdateState() 前必须通过 Init() 注册状态转换表。
 */
#if defined(__cplusplus) && __cplusplus >= 202002L
template <StateEnumType State>
#else
template <typename State, typename = typename std::enable_if_t<std::is_enum_v<State>>>
#endif
class StateMachineSwitcher
{
public:
    using StateType = State;
    using Atomic_State = std::atomic<StateType>;

public:
    /** @brief 构造状态切换基类并使用默认状态上下文。 */
    StateMachineSwitcher() noexcept = default;
    StateMachineSwitcher(const StateMachineSwitcher &) = delete;
    StateMachineSwitcher &operator=(const StateMachineSwitcher &) = delete;
    StateMachineSwitcher(StateMachineSwitcher &&) noexcept = delete;
    StateMachineSwitcher &operator=(StateMachineSwitcher &&) noexcept = delete;

    /** @brief 提供多态销毁支持。 */
    virtual ~StateMachineSwitcher() = default;

private:
    inline static Atomic_State crnt_state_{static_cast<StateType>(0)};
    inline static Atomic_State last_state_{static_cast<StateType>(0)};
    inline static Atomic_State prvs_state_{static_cast<StateType>(0)};
    inline static uint32_t count_{0};
    inline static steady_clock::time_point steady_start_time_{steady_clock::now()};
    inline static seconds duration_{0};
    inline static FuncOpenType open_type_{FuncOpenType::NONE_0};
    inline static FuncActvType actv_type_{FuncActvType::NONE_0};

private:
    uint32_t freq_{20};
    StateSwitchTable<StateType> table_{};

public:
    /**
     * @brief 初始化派生状态机的状态转换表。
     * @details 派生类应通过 AddStateSwitch() 注册全部可达状态及转换条件。
     */
    virtual void Init() = 0;

    /**
     * @brief 输出派生状态机的状态诊断信息。
     * @details 由 PrintInfo() 在状态变化或达到周期输出条件时调用。
     */
    virtual void PrintStateInfo(bool flag = false) const
    {

    }

    virtual void Print() const = 0;
private:
    StateType CalcNextState() const noexcept
    {
        StateType crnt_state = GetCrntState();
        const auto &state_switch_list = table_.GetStateSwitchTable(crnt_state);
        for (auto iter = std::cbegin(state_switch_list); iter != std::cend(state_switch_list); ++iter)
        {
            auto & switch_function = iter->second;
            if (switch_function())
            {
                crnt_state = iter->first;
                // 第一个条件成立的目标状态即为下一个状态，后续条件不再判断
                break;
            }
        }
        return crnt_state;
    }
    /**
     * @brief 按需输出状态诊断信息。
     * @details 状态发生变化时立即输出；处于值不小于 2 的稳定状态时，
     * 按频率间隔输出。
     */
    void PrintInfo() const noexcept
    {
        if (IsStateChanged())
        {
            PrintStateInfo(true);
        }
        else 
        {
            if (crnt_state_ >= static_cast<StateType>(2))
            {
                if (GetCount() % (GetFrequency() * 60) == 0)
                {
                    PrintStateInfo(false);
                }
            }
        }
    }


    /**
     * @brief 将状态机更新至指定状态。
     * @param state 要设置的目标状态。
     * @details 状态变化时保存前序状态、重置计数和计时起点；随后更新上一和
     * 当前状态、周期计数及持续时间，并触发状态信息输出。
     */
    void UpdateState(StateType state) noexcept
    {
        if (crnt_state_.load() != state)
        {
            SetPrvsState(crnt_state_.load());
            ResetCount();
            ResetStartSteadyTime();
            ResetDuration();
        }
        SetLastState(crnt_state_.load());
        SetCrntState(state);
        SetCount(GetCount() + 1);
        SetDuration(duration_cast<seconds>(steady_clock::now() - steady_start_time_));
        // PrintInfo();
        Print();
    }
    
public:
    /**
     * @brief 根据已注册的转换条件计算并更新下一个状态。
     * @details 按转换表中的顺序选择首个条件成立的目标状态；没有条件成立时
     * 保持当前状态。
     */
    void UpdateState()
    {
        UpdateState(CalcNextState());
    }

public:
    /** @brief 获取当前状态。 @return 当前状态枚举值。 */
    static StateType GetCrntState() noexcept
    {
        return crnt_state_.load();
    }

    /** @brief 获取上一周期状态。 @return 上一状态枚举值。 */
    static StateType GetLastState() noexcept
    {
        return last_state_.load();
    }

    /** @brief 获取最近一次状态变化前的状态。 @return 前序状态枚举值。 */
    static StateType GetPrvsState() noexcept
    {
        return prvs_state_.load();
    }

    /** @brief 获取当前状态的周期计数。 @return 自进入当前状态后的更新次数。 */
    static uint32_t GetCount() noexcept
    {
        return count_;
    }

    /** @brief 获取当前状态的计时起点。 @return 稳态时钟时间点。 */
    static const steady_clock::time_point& GetStartSteadyTime() noexcept
    {
        return steady_start_time_;
    }

    /** @brief 获取当前状态已持续的时间。 @return 以秒为单位的持续时间。 */
    static const seconds& GetDuration() noexcept
    {
        return duration_;
    }

    /** @brief 获取当前功能开启类型。 @return 功能开启类型枚举值。 */
    static FuncOpenType GetOpenType() noexcept
    {
        return open_type_;
    }

    /** @brief 获取当前功能激活类型。 @return 功能激活类型枚举值。 */
    static FuncActvType GetActvType() noexcept
    {
        return actv_type_;
    }
protected:
    uint32_t GetFrequency() const noexcept
    {
        return freq_;
    }
public:
    /** @brief 判断当前状态是否相对于上一状态发生变化。 */
    static bool IsStateChanged() noexcept
    {
        return crnt_state_.load() != last_state_.load();
    }

    /** @brief 判断本周期是否切换至指定状态。 @param state 目标状态。 */
    static bool IsChangeTo(StateType state) noexcept
    {
        return crnt_state_.load() == state && last_state_.load() != state;
    }

    /** @brief 判断本周期是否从指定状态切出。 @param state 源状态。 */
    static bool IsChangeFrom(StateType state) noexcept
    {
        return last_state_.load() == state && crnt_state_.load() != state;
    }

    /**
     * @brief 判断本周期是否从指定源状态切换至指定目标状态。
     * @param from 源状态。
     * @param to 目标状态。
     */
    static bool IsChangeFromTo(StateType from, StateType to) noexcept
    {
        return last_state_.load() == from && crnt_state_.load() == to;
    }

public:
    /** @brief 设置当前状态。 @param state 新当前状态，默认状态值为 0。 */
    static void SetCrntState(StateType state = static_cast<StateType>(0)) noexcept
    {
        crnt_state_.store(state);
    }

    /** @brief 设置上一状态。 @param state 新上一状态，默认状态值为 0。 */
    static void SetLastState(StateType state = static_cast<StateType>(0)) noexcept
    {
        last_state_.store(state);
    }

    /** @brief 设置前序状态。 @param state 新前序状态，默认状态值为 0。 */
    static void SetPrvsState(StateType state = static_cast<StateType>(0)) noexcept
    {
        prvs_state_.store(state);
    }

    /** @brief 设置当前状态周期计数。 @param count 新计数，默认值为 0。 */
    static void SetCount(uint32_t count = 0) noexcept
    {
        count_ = count;
    }

    static void ResetCount() noexcept
    {
        count_ = 0;
    }

    /**
     * @brief 设置当前状态的计时起点。
     * @tparam U 稳态时钟时间点类型。
     * @param time_point 新计时起点。
     */
    template <typename U, typename = typename std::enable_if_t<is_decay_same<U, steady_clock::time_point>::value>>
    static void SetStartSteadyTime(U && time_point) noexcept
    {
        steady_start_time_ = std::forward<U>(time_point);
    }

    static void ResetStartSteadyTime() noexcept
    {
        steady_start_time_ = steady_clock::now();
    }

    /**
     * @brief 设置当前状态持续时间。
     * @tparam U 秒级持续时间类型。
     * @param duration 新持续时间。
     */
    template <typename U, typename = typename std::enable_if_t<is_decay_same<U, seconds>::value>>
    static void SetDuration(U && duration) noexcept
    {
        duration_ = std::forward<U>(duration);
    }

    static void ResetDuration() noexcept
    {
        duration_ = seconds(0);
    }

    /** @brief 设置功能开启类型。 @param open_type 新开启类型，默认 NONE_0。 */
    static void SetOpenType(FuncOpenType open_type = FuncOpenType::NONE_0) noexcept
    {
        open_type_ = open_type;
    }

    /** @brief 设置功能激活类型。 @param actv_type 新激活类型，默认 NONE_0。 */
    static void SetActvType(FuncActvType actv_type = FuncActvType::NONE_0) noexcept
    {
        actv_type_ = actv_type;
    }
protected:
    /**
     * @brief 注册某个源状态的目标状态及转换条件表。
     * @param from_state 源状态。
     * @param table 目标状态到转换条件的映射，调用后其内容会被移动。
     */
    void AddStateSwitch(StateType from_state, typename StateSwitchTable<StateType>::SwitchSubTable &&table)
    {
        table_.AddStateSwitch(from_state, std::move(table));
    }
};