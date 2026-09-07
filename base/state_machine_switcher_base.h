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
 * @brief 提供枚举状态机的通用状态转换与状态上下文管理。
 *
 * @details
 * 派生类通过 Init() 注册源状态、目标状态及转换条件，并通过 PrintStateInfo()
 * 实现状态信息输出。UpdateState() 会计算或接收下一个状态，维护当前、上一和
 * 前序状态、当前状态周期计数及持续时间，并在状态变化或达到输出周期时触发打印。
 *
 * 当前、上一、前序状态以及功能开启和激活类型为按 State 模板实参共享的静态状态；
 * 因此相同状态枚举类型的多个切换器实例会共享这些状态上下文。转换表与执行频率
 * 则属于单个实例。
 *
 * @tparam State 状态枚举类型，必须为枚举。
 * @note 调用 UpdateState() 前，派生类必须先调用 Init() 注册状态转换表。
 */
template <typename State, typename = typename std::enable_if_t<std::is_enum_v<State>>>
class StateMachineSwitcherBase
{
public:
    using StateType = State;
    using atomic_T = std::atomic<StateType>;
public:
    /** @brief 构造状态切换基类并使用默认状态上下文。 */
    StateMachineSwitcherBase() noexcept = default;

    /** @brief 提供多态销毁支持。 */
    virtual ~StateMachineSwitcherBase() = default;
private:
    inline static atomic_T crnt_state_{static_cast<StateType>(0)};
    inline static atomic_T last_state_{static_cast<StateType>(0)};
    inline static atomic_T prvs_state_{static_cast<StateType>(0)};
    inline static uint32_t count_{0};
    inline static steady_clock::time_point steady_start_time_{steady_clock::now()};
    inline static seconds duration_{0};
    inline static FuncOpenType open_type_{FuncOpenType::NONE_0};
    inline static FuncActvType actv_type_{FuncActvType::NONE_0};
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
    virtual void PrintStateInfo(bool flag = false) = 0;
private:
    StateType CalcNextState()
    {
        StateType crnt_state = GetCrntState();
        const auto &state_switch_list = table_.GetStateSwitchTable(crnt_state);
        for (auto iter = std::cbegin(state_switch_list); iter != std::cend(state_switch_list); ++iter)
        {
            auto to_state = iter->first;
            auto switch_function = iter->second;
            if (switch_function())
            {
                crnt_state = to_state;
                break;
            }
        }
        return crnt_state;
    }
public:
    /**
     * @brief 按需输出状态诊断信息。
     * @details 状态发生变化时立即输出；处于值不小于 2 的稳定状态时，
     * 按频率间隔输出。
     */
    void PrintInfo()
    {
        if (IsStateChanged())
        {
            PrintStateInfo(true);
        }
        else 
        {
            if (crnt_state_ >= static_cast<StateType>(2))
            {
                if (GetCount() % (GetFrequency() * 2) == 0)
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
        PrintInfo();
    }

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
private:
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
    void AddStateSwitch(StateType from_state, StateSwitchTable<StateType>::SwitchSubTable &&table)
    {
        table_.AddStateSwitch(from_state, std::move(table));
    }
};