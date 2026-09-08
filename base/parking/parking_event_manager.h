#pragma once

#include <type_traits>
#include <variant>
#include <stdexcept>
#include <iostream> 
#include "parking_event_enum.h"

namespace parking
{

/**
 * @brief 统一保存停车功能事件标志的基础类。
 *
 * 业务事件类负责自己的强类型条件枚举和业务语义；本类只负责通用的
 * 8 个业务事件标志，避免各功能重复实现相同的数组、查询、
 * 设置和重置逻辑。
 */
class ParkingEventManager
{
public:
    using EventValue = std::variant<PrkgFuncActvType,
                                    PrkgFuncActvIhbtType,
                                    PrkgFuncGuidanceType,
                                    PrkgFuncGuidanceIhbtType,
                                    PrkgFuncPauseType,
                                    PrkgFuncSuccessType,
                                    PrkgFuncFailType,
                                    PrkgFuncExitType>;

private:
    /** @brief 激活事件成员。 */
    inline static PrkgFuncActvType actv_{static_cast<PrkgFuncActvType>(0)};
    /** @brief 激活抑制事件成员。 */
    inline static PrkgFuncActvIhbtType actv_inhibited_{static_cast<PrkgFuncActvIhbtType>(0)};
    /** @brief 控车激活事件成员。 */
    inline static PrkgFuncGuidanceType guidance_{static_cast<PrkgFuncGuidanceType>(0)};
    /** @brief 控车激活抑制事件成员。 */
    inline static PrkgFuncGuidanceIhbtType guidance_inhibited_{static_cast<PrkgFuncGuidanceIhbtType>(0)};
    /** @brief 暂停事件成员。 */
    inline static PrkgFuncPauseType pause_{static_cast<PrkgFuncPauseType>(0)};
    /** @brief 成功事件成员。 */
    inline static PrkgFuncSuccessType success_{static_cast<PrkgFuncSuccessType>(0)};
    /** @brief 失败事件成员。 */
    inline static PrkgFuncFailType fail_{static_cast<PrkgFuncFailType>(0)};
    /** @brief 退出事件成员。 */
    inline static PrkgFuncExitType exit_{static_cast<PrkgFuncExitType>(0)};
protected:
    virtual void LogEventChange(ParkingEventType event_type, int value) noexcept = 0;
private:
    /**
     * @brief 检查指定事件是否已设置。
     * @tparam EventType 事件类型，必须是枚举类型。
     * @param event 要检查的事件。
     * @return 事件底层值不为 0 时返回 true。
     */
    template <typename EventType>
    static bool IsEventSet(EventType event) noexcept
    {
        return static_cast<std::underlying_type_t<EventType>>(event) != 0;
    }

public:
    /**
     * @brief 获取激活事件值。
     * @return 当前激活事件的具体枚举值。
     */
    static PrkgFuncActvType GetActv() noexcept
    {
        return actv_;
    }

    /**
     * @brief 获取激活抑制事件值。
     * @return 当前激活抑制事件的具体枚举值。
     */
    static PrkgFuncActvIhbtType GetActvInhibited() noexcept
    {
        return actv_inhibited_;
    }

    /**
     * @brief 获取控车激活事件值。
     * @return 当前控车激活事件的具体枚举值。
     */
    static PrkgFuncGuidanceType GetGuidance() noexcept
    {
        return guidance_;
    }

    /**
     * @brief 获取控车激活抑制事件值。
     * @return 当前控车激活抑制事件的具体枚举值。
     */
    static PrkgFuncGuidanceIhbtType GetGuidanceInhibited() noexcept
    {
        return guidance_inhibited_;
    }

    /**
     * @brief 获取暂停事件值。
     * @return 当前暂停事件的具体枚举值。
     */
    static PrkgFuncPauseType GetPause() noexcept
    {
        return pause_;
    }

    /**
     * @brief 获取成功事件值。
     * @return 当前成功事件的具体枚举值。
     */
    static PrkgFuncSuccessType GetSuccess() noexcept
    {
        return success_;
    }

    /**
     * @brief 获取失败事件值。
     * @return 当前失败事件的具体枚举值。
     */
    static PrkgFuncFailType GetFail() noexcept
    {
        return fail_;
    }

    /**
     * @brief 获取退出事件值。
     * @return 当前退出事件的具体枚举值。
     */
    static PrkgFuncExitType GetExit() noexcept
    {
        return exit_;
    }

    /**
     * @brief 获取指定事件对应的具体枚举值。
     *
     * 返回值使用 std::variant 保存 8 种模板枚举类型之一。调用方可以
     * 使用 std::get、std::holds_alternative 或 std::visit 获取具体类型。
     * 当 event 为 NONE_0 或无效值时抛出 std::invalid_argument。
     *
     * @param event 要获取的通用停车事件。
     * @return 对应事件成员的具体枚举值。
     */
    static EventValue GetEventValue(ParkingEventType event) noexcept
    {
        switch (event)
        {
            case ParkingEventType::ACTV_1: return actv_;
            case ParkingEventType::ACTV_IHBT_2: return actv_inhibited_;
            case ParkingEventType::GUIDANCE_3: return guidance_;
            case ParkingEventType::GUIDANCE_IHBT_4: return guidance_inhibited_;
            case ParkingEventType::PAUSE_5: return pause_;
            case ParkingEventType::SUCCESS_6: return success_;
            case ParkingEventType::FAIL_7: return fail_;
            case ParkingEventType::EXIT_8: return exit_;
            case ParkingEventType::NONE_0:
            default: return actv_; // Return a default value for NONE_0 or invalid event
        }
    }

    /**
     * @brief 获取当前设置的通用停车事件类型。
     * @return 当前设置的通用停车事件类型。
     */
    static ParkingEventType GetEventType() noexcept
    {
        if (IsEventSet(actv_))
        {
            return ParkingEventType::ACTV_1;
        }
        else if (IsEventSet(actv_inhibited_))
        {
            return ParkingEventType::ACTV_IHBT_2;
        }
        else if (IsEventSet(guidance_))
        {
            return ParkingEventType::GUIDANCE_3;
        }
        else if (IsEventSet(guidance_inhibited_))
        {
            return ParkingEventType::GUIDANCE_IHBT_4;
        }
        else if (IsEventSet(pause_))
        {
            return ParkingEventType::PAUSE_5;
        }
        else if (IsEventSet(success_))
        {
            return ParkingEventType::SUCCESS_6;
        }
        else if (IsEventSet(fail_))
        {
            return ParkingEventType::FAIL_7;
        }
        else if (IsEventSet(exit_))
        {
            return ParkingEventType::EXIT_8;
        }
        else
        {
            return ParkingEventType::NONE_0;
        }
    }

    /**
     * @brief 查询指定通用停车事件是否已设置。
     * @param event 要查询的通用停车事件。
     * @return 事件已设置时返回 true。
     */
    static bool GetEventFlag() noexcept
    {
        return GetEventType() != ParkingEventType::NONE_0;
    }

    /**
     * @brief 设置激活事件的具体枚举值。
     * @param value 要设置的激活事件值。
     */
    static void SetActv(PrkgFuncActvType value) noexcept 
    { 
        actv_ = value;
        // LogEventChange(ParkingEventType::ACTV_1,
        //             static_cast<int>(static_cast<std::underlying_type_t<ActvType>>(value)));
    }

    /**
     * @brief 设置激活抑制事件的具体枚举值。
     * @param value 要设置的激活抑制事件值。
     */
    static void SetActvInhibited(PrkgFuncActvIhbtType value) noexcept 
    { 
        actv_inhibited_ = value; 
        // LogEventChange(ParkingEventType::ACTV_IHBT_2,
        //            static_cast<int>(static_cast<std::underlying_type_t<ActvIhbtType>>(value)));
    }

    /**
     * @brief 设置控车激活事件的具体枚举值。
     * @param value 要设置的控车激活事件值。
     */
    static void SetGuidance(PrkgFuncGuidanceType value) noexcept 
    { 
        guidance_ = value; 
        // LogEventChange(ParkingEventType::GUIDANCE_3,
        //            static_cast<int>(static_cast<std::underlying_type_t<GuidanceType>>(value)));
    }

    /**
     * @brief 设置控车激活抑制事件的具体枚举值。
     * @param value 要设置的控车激活抑制事件值。
     */
    static void SetGuidanceInhibited(PrkgFuncGuidanceIhbtType value) noexcept
    {
        guidance_inhibited_ = value;
        // LogEventChange(ParkingEventType::GUIDANCE_IHBT_4,
        //            static_cast<int>(static_cast<std::underlying_type_t<GuidanceIhbtType>>(value)));
    }

    /**
     * @brief 设置暂停事件的具体枚举值。
     * @param value 要设置的暂停事件值。
     */
    static void SetPause(PrkgFuncPauseType value) noexcept 
    { 
        pause_ = value; 
        // LogEventChange(ParkingEventType::PAUSE_5,
        //            static_cast<int>(static_cast<std::underlying_type_t<PauseType>>(value)));
    }

    /**
     * @brief 设置成功事件的具体枚举值。
     * @param value 要设置的成功事件值。
     */
    static void SetSuccess(PrkgFuncSuccessType value) noexcept 
    { 
        success_ = value; 
        // LogEventChange(ParkingEventType::SUCCESS_6,
        //            static_cast<int>(static_cast<std::underlying_type_t<SuccessType>>(value)));
    }

    /**
     * @brief 设置失败事件的具体枚举值。
     * @param value 要设置的失败事件值。
     */
    static void SetFail(PrkgFuncFailType value) noexcept 
    { 
        fail_ = value; 
        // LogEventChange(ParkingEventType::FAIL_7,
        //            static_cast<int>(static_cast<std::underlying_type_t<FailType>>(value)));
    }

    /**
     * @brief 设置退出事件的具体枚举值。
     * @param value 要设置的退出事件值。
     */
    static void SetExit(PrkgFuncExitType value) noexcept 
    { 
        exit_ = value; 
        // LogEventChange(ParkingEventType::EXIT_8,
        //            static_cast<int>(static_cast<std::underlying_type_t<ExitType>>(value)));
    }

    static void SetEvent(EventValue value) noexcept
    {
        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, PrkgFuncActvType>) 
            {
                SetActv(arg);
            } 
            else if constexpr (std::is_same_v<T, PrkgFuncActvIhbtType>) 
            {
                SetActvInhibited(arg);
            } 
            else if constexpr (std::is_same_v<T, PrkgFuncGuidanceType>) 
            {
                SetGuidance(arg);
            } 
            else if constexpr (std::is_same_v<T, PrkgFuncGuidanceIhbtType>) 
            {
                SetGuidanceInhibited(arg);
            } 
            else if constexpr (std::is_same_v<T, PrkgFuncPauseType>) 
            {
                SetPause(arg);
            } 
            else if constexpr (std::is_same_v<T, PrkgFuncSuccessType>) 
            {
                SetSuccess(arg);
            } 
            else if constexpr (std::is_same_v<T, PrkgFuncFailType>) 
            {
                SetFail(arg);
            } 
            else if constexpr (std::is_same_v<T, PrkgFuncExitType>)
            {
                SetExit(arg);
            }
        }, value);
    }

    /** @brief 清除全部通用事件标志。 */
    static void Reset() noexcept
    {
        actv_ = static_cast<PrkgFuncActvType>(0);
        actv_inhibited_ = static_cast<PrkgFuncActvIhbtType>(0);
        guidance_ = static_cast<PrkgFuncGuidanceType>(0);
        guidance_inhibited_ = static_cast<PrkgFuncGuidanceIhbtType>(0);
        pause_ = static_cast<PrkgFuncPauseType>(0);
        success_ = static_cast<PrkgFuncSuccessType>(0);
        fail_ = static_cast<PrkgFuncFailType>(0);
        exit_ = static_cast<PrkgFuncExitType>(0);
    }
};

}  // namespace parking
