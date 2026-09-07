#pragma once

#include <type_traits>
#include <variant>
#include <stdexcept>
#include <iostream>
#include "parking_event_base.h"
#include "parking_event_enum.h"

namespace parking
{

/**
 * @brief 统一保存停车功能事件标志的基础类。
 *
 * 业务事件类负责自己的强类型条件枚举和业务语义；本类只负责通用的
 * 8 个业务事件标志，避免各功能重复实现相同的数组、查询、
 * 设置和重置逻辑。
 *
 * @tparam ActvType 激活事件类型。
 * @tparam ActvIhbtType 激活抑制事件类型。
 * @tparam GuidanceType 控车激活事件类型。
 * @tparam GuidanceIhbtType 控车激活抑制事件类型。
 * @tparam PauseType 暂停事件类型。
 * @tparam SuccessType 成功事件类型。
 * @tparam FailType 失败事件类型。
 * @tparam ExitType 退出事件类型。
 */
template <typename ActvType,
          typename ActvIhbtType,
          typename GuidanceType,
          typename GuidanceIhbtType,
          typename PauseType,
          typename SuccessType,
          typename FailType,
          typename ExitType>
class ParkingEventManager
{
public:
    static_assert(std::is_enum_v<ActvType> &&
                      std::is_enum_v<ActvIhbtType> &&
                      std::is_enum_v<GuidanceType> &&
                      std::is_enum_v<GuidanceIhbtType> &&
                      std::is_enum_v<PauseType> &&
                      std::is_enum_v<SuccessType> &&
                      std::is_enum_v<FailType> &&
                      std::is_enum_v<ExitType>,
                  "Parking event template arguments must be enums");
    using EventBase = ParkingEventBase<ActvType, ActvIhbtType, GuidanceType, GuidanceIhbtType, PauseType, SuccessType, FailType, ExitType>;
    /**
     * @brief 保存 8 种通用停车事件具体枚举值的变体类型。
     */
    using EventValue = std::variant<ActvType,
                                    ActvIhbtType,
                                    GuidanceType,
                                    GuidanceIhbtType,
                                    PauseType,
                                    SuccessType,
                                    FailType,
                                    ExitType>;   

private:
    /**
     * @brief 当前模板实例共享的停车事件状态。
     *
     * 同一组模板枚举类型对应的所有 ParkingEventManager 实例共用此状态。
     */
    inline static EventBase event_base_{};
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
     * @brief 获取当前的事件基类实例。
     * @return 当前事件基类实例。
     */
    static EventBase GetEvent() noexcept
    {
        return event_base_;
    }

    /**
     * @brief 获取激活事件值。
     * @return 当前激活事件的具体枚举值。
     */
    static ActvType GetActv() noexcept
    {
        return event_base_.actv_;
    }

    /**
     * @brief 获取激活抑制事件值。
     * @return 当前激活抑制事件的具体枚举值。
     */
    static ActvIhbtType GetActvInhibited() noexcept
    {
        return event_base_.actv_inhibited_;
    }

    /**
     * @brief 获取控车激活事件值。
     * @return 当前控车激活事件的具体枚举值。
     */
    static GuidanceType GetGuidance() noexcept
    {
        return event_base_.guidance_;
    }

    /**
     * @brief 获取控车激活抑制事件值。
     * @return 当前控车激活抑制事件的具体枚举值。
     */
    static GuidanceIhbtType GetGuidanceInhibited() noexcept
    {
        return event_base_.guidance_inhibited_;
    }

    /**
     * @brief 获取暂停事件值。
     * @return 当前暂停事件的具体枚举值。
     */
    static PauseType GetPause() noexcept
    {
        return event_base_.pause_;
    }

    /**
     * @brief 获取成功事件值。
     * @return 当前成功事件的具体枚举值。
     */
    static SuccessType GetSuccess() noexcept
    {
        return event_base_.success_;
    }

    /**
     * @brief 获取失败事件值。
     * @return 当前失败事件的具体枚举值。
     */
    static FailType GetFail() noexcept
    {
        return event_base_.fail_;
    }

    /**
     * @brief 获取退出事件值。
     * @return 当前退出事件的具体枚举值。
     */
    static ExitType GetExit() noexcept
    {
        return event_base_.exit_;
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
    static EventValue GetEventType(ParkingEventType event) noexcept
    {
        switch (event)
        {
            case ParkingEventType::ACTV_1: return event_base_.actv_;
            case ParkingEventType::ACTV_IHBT_2: return event_base_.actv_inhibited_;
            case ParkingEventType::GUIDANCE_3: return event_base_.guidance_;
            case ParkingEventType::GUIDANCE_IHBT_4: return event_base_.guidance_inhibited_;
            case ParkingEventType::PAUSE_5: return event_base_.pause_;
            case ParkingEventType::SUCCESS_6: return event_base_.success_;
            case ParkingEventType::FAIL_7: return event_base_.fail_;
            case ParkingEventType::EXIT_8: return event_base_.exit_;
            case ParkingEventType::NONE_0:
            default: ActvType::NONE_0; // Return a default value for NONE_0 or invalid event·
        }
    }

    /**
     * @brief 获取当前设置的通用停车事件类型。
     * @return 当前设置的通用停车事件类型。
     */
    static ParkingEventType GetEventType() noexcept
    {
        if (IsEventSet(event_base_.actv_))
        {
            return ParkingEventType::ACTV_1;
        }
        else if (IsEventSet(event_base_.actv_inhibited_))
        {
            return ParkingEventType::ACTV_IHBT_2;
        }
        else if (IsEventSet(event_base_.guidance_))
        {
            return ParkingEventType::GUIDANCE_3;
        }
        else if (IsEventSet(event_base_.guidance_inhibited_))
        {
            return ParkingEventType::GUIDANCE_IHBT_4;
        }
        else if (IsEventSet(event_base_.pause_))
        {
            return ParkingEventType::PAUSE_5;
        }
        else if (IsEventSet(event_base_.success_))
        {
            return ParkingEventType::SUCCESS_6;
        }
        else if (IsEventSet(event_base_.fail_))
        {
            return ParkingEventType::FAIL_7;
        }
        else if (IsEventSet(event_base_.exit_))
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
    static bool GetEventFlag(ParkingEventType event) noexcept
    {
        switch (event)
        {
            case ParkingEventType::ACTV_1: return IsEventSet(event_base_.actv_);
            case ParkingEventType::ACTV_IHBT_2: return IsEventSet(event_base_.actv_inhibited_);
            case ParkingEventType::GUIDANCE_3: return IsEventSet(event_base_.guidance_);
            case ParkingEventType::GUIDANCE_IHBT_4: return IsEventSet(event_base_.guidance_inhibited_);
            case ParkingEventType::PAUSE_5: return IsEventSet(event_base_.pause_);
            case ParkingEventType::SUCCESS_6: return IsEventSet(event_base_.success_);
            case ParkingEventType::FAIL_7: return IsEventSet(event_base_.fail_);
            case ParkingEventType::EXIT_8: return IsEventSet(event_base_.exit_);
            case ParkingEventType::NONE_0:
            default: return false;
        }
    }

    /**
     * @brief 设置激活事件的具体枚举值。
     * @param value 要设置的激活事件值。
     */
    static void SetActv(ActvType value) noexcept 
    { 
        if (value != event_base_.actv_)
        {
            std::cout << "event_base_.actv_ : " << static_cast<int>(event_base_.actv_) << " -> " << static_cast<int>(value) << std::endl;
        }
        event_base_.actv_ = value;
        // LogEventChange(ParkingEventType::ACTV_1,
        //             static_cast<int>(static_cast<std::underlying_type_t<ActvType>>(value)));
    }

    /**
     * @brief 设置激活抑制事件的具体枚举值。
     * @param value 要设置的激活抑制事件值。
     */
    static void SetActvInhibited(ActvIhbtType value) noexcept 
    { 
        event_base_.actv_inhibited_ = value; 
        // LogEventChange(ParkingEventType::ACTV_IHBT_2,
        //            static_cast<int>(static_cast<std::underlying_type_t<ActvIhbtType>>(value)));
    }

    /**
     * @brief 设置控车激活事件的具体枚举值。
     * @param value 要设置的控车激活事件值。
     */
    static void SetGuidance(GuidanceType value) noexcept 
    { 
        if (value != event_base_.guidance_)
        {
            std::cout << "event_base_.guidance_ : " << static_cast<int>(event_base_.guidance_) << " -> " << static_cast<int>(value) << std::endl;
        }
        event_base_.guidance_ = value; 
        // LogEventChange(ParkingEventType::GUIDANCE_3,
        //            static_cast<int>(static_cast<std::underlying_type_t<GuidanceType>>(value)));
    }

    /**
     * @brief 设置控车激活抑制事件的具体枚举值。
     * @param value 要设置的控车激活抑制事件值。
     */
    static void SetGuidanceInhibited(GuidanceIhbtType value) noexcept
    {
        event_base_.guidance_inhibited_ = value;
        // LogEventChange(ParkingEventType::GUIDANCE_IHBT_4,
        //            static_cast<int>(static_cast<std::underlying_type_t<GuidanceIhbtType>>(value)));
    }

    /**
     * @brief 设置暂停事件的具体枚举值。
     * @param value 要设置的暂停事件值。
     */
    static void SetPause(PauseType value) noexcept 
    { 
        event_base_.pause_ = value; 
        // LogEventChange(ParkingEventType::PAUSE_5,
        //            static_cast<int>(static_cast<std::underlying_type_t<PauseType>>(value)));
    }

    /**
     * @brief 设置成功事件的具体枚举值。
     * @param value 要设置的成功事件值。
     */
    static void SetSuccess(SuccessType value) noexcept 
    { 
        if (value != event_base_.success_)
        {
            std::cout << "event_base_.success_ : " << static_cast<int>(event_base_.success_) << " -> " << static_cast<int>(value) << std::endl;
        }
        event_base_.success_ = value; 
        // LogEventChange(ParkingEventType::SUCCESS_6,
        //            static_cast<int>(static_cast<std::underlying_type_t<SuccessType>>(value)));
    }

    /**
     * @brief 设置失败事件的具体枚举值。
     * @param value 要设置的失败事件值。
     */
    static void SetFail(FailType value) noexcept 
    { 
        event_base_.fail_ = value; 
        // LogEventChange(ParkingEventType::FAIL_7,
        //            static_cast<int>(static_cast<std::underlying_type_t<FailType>>(value)));
    }

    /**
     * @brief 设置退出事件的具体枚举值。
     * @param value 要设置的退出事件值。
     */
    static void SetExit(ExitType value) noexcept 
    { 
        if (value != event_base_.exit_)
        {
            std::cout << "event_base_.exit_ : " << static_cast<int>(event_base_.exit_) << " -> " << static_cast<int>(value) << std::endl;
        }
        event_base_.exit_ = value; 
        // LogEventChange(ParkingEventType::EXIT_8,
        //            static_cast<int>(static_cast<std::underlying_type_t<ExitType>>(value)));
    }

    /**
     * @brief 设置指定通用停车事件的具体枚举值。
     * @param event 要设置的通用停车事件。
     * @param value 对应事件的具体枚举值。
     *              当 event 为 NONE_0 或无效值时，value 会被忽略。
     */
    static void SetEvent(ParkingEventType event, EventValue value) noexcept
    {
        switch (event)
        {
            case ParkingEventType::ACTV_1: SetActv(std::get<ActvType>(value)); break;
            case ParkingEventType::ACTV_IHBT_2: SetActvInhibited(std::get<ActvIhbtType>(value)); break;
            case ParkingEventType::GUIDANCE_3: SetGuidance(std::get<GuidanceType>(value)); break;
            case ParkingEventType::GUIDANCE_IHBT_4: SetGuidanceInhibited(std::get<GuidanceIhbtType>(value)); break;
            case ParkingEventType::PAUSE_5: SetPause(std::get<PauseType>(value)); break;
            case ParkingEventType::SUCCESS_6: SetSuccess(std::get<SuccessType>(value)); break;
            case ParkingEventType::FAIL_7: SetFail(std::get<FailType>(value)); break;
            case ParkingEventType::EXIT_8: SetExit(std::get<ExitType>(value)); break;
            case ParkingEventType::NONE_0:
            default: break;
        }
    }

    static void SetEvent(EventValue value) noexcept
    {
        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, ActvType>) 
            {
                SetActv(arg);
            } 
            else if constexpr (std::is_same_v<T, ActvIhbtType>) 
            {
                SetActvInhibited(arg);
            } 
            else if constexpr (std::is_same_v<T, GuidanceType>) 
            {
                SetGuidance(arg);
            } 
            else if constexpr (std::is_same_v<T, GuidanceIhbtType>) 
            {
                SetGuidanceInhibited(arg);
            } 
            else if constexpr (std::is_same_v<T, PauseType>) 
            {
                SetPause(arg);
            } 
            else if constexpr (std::is_same_v<T, SuccessType>) 
            {
                SetSuccess(arg);
            } 
            else if constexpr (std::is_same_v<T, FailType>) 
            {
                SetFail(arg);
            } 
            else if constexpr (std::is_same_v<T, ExitType>) 
            {
                SetExit(arg);
            }
        }, value);
    }

    /** @brief 清除全部通用事件标志。 */
    static void Reset() noexcept
    {
        event_base_.actv_ = static_cast<ActvType>(0);
        event_base_.actv_inhibited_ = static_cast<ActvIhbtType>(0);
        event_base_.guidance_ = static_cast<GuidanceType>(0);
        event_base_.guidance_inhibited_ = static_cast<GuidanceIhbtType>(0);
        event_base_.pause_ = static_cast<PauseType>(0);
        event_base_.success_ = static_cast<SuccessType>(0);
        event_base_.fail_ = static_cast<FailType>(0);
        event_base_.exit_ = static_cast<ExitType>(0);
    }
};

}  // namespace parking
