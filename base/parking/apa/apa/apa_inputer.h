#pragma once

#include "apa_event.h"
#include "apa_param.h"
#include "apa_switcher.h"
#include "apa_event_manager.h"
#include "../../../state_machine_inputer_base.h"

#include <iostream>

namespace parking
{
    /**
     * @brief 为 APA 状态机提供外部事件输入。
     *
     * @details
     * 该输入器持有 ApaEvent 实例，并作为状态机输入层的 APA 专用实现。
     * InitReaders() 负责初始化事件读取通道，UpdateEvent() 负责将读取到的
     * 外部信息更新至事件对象，供状态切换逻辑使用。
     *
     * @note 当前 UpdateEvent() 尚未接入实际事件源，因此不会修改事件数据。
     */
    class ApaInputer final : public StateMachineInputerBase
    {
    public:
        /**
         * @brief 构造 APA 状态机输入器。
         *
         * @details 创建 ApaEvent 并传递给状态机输入基类，作为 APA 事件数据的载体。
         */
        ApaInputer() : StateMachineInputerBase(std::make_shared<ApaEvent>()) {}

    public:
        /**
         * @brief 初始化 APA 事件读取通道。
         *
         * @details 当前实现输出初始化日志，保留该重写点以便后续接入实际 reader。
         */
        void InitReaders() override
        {
            std::cout << "[StateMachine] Init ApaInputer Readers" << std::endl;
        }

        /**
         * @brief 更新 APA 状态机使用的事件数据。
         *
         * @details 当前为空实现，尚未从外部 reader 获取数据或更新 ApaEvent。
         */
        void UpdateEvent() override 
        {
            if (true)
            {
                ApaEventManager::Reset();
                if (ApaStateSwitcher::GetCrntState() == ApaStateType::STANDBY_1 && ApaStateSwitcher::GetCount() >= 60)
                {
                    ApaEventManager::SetActv(ApaActvType::BTN_1);
                }
                else if (ApaStateSwitcher::GetCrntState() == ApaStateType::PREPARED_4 && ApaStateSwitcher::GetCount()  >= 60)
                {
                    ApaEventManager::SetGuidance(ApaGuidanceType::AUTO_5);
                }
                else if (ApaStateSwitcher::GetCrntState() == ApaStateType::PARKING_6 && ApaStateSwitcher::GetCount()  >= 60)
                {
                    ApaEventManager::SetSuccess(ApaSuccessType::DATA_VALID_1);
                }
                else if (ApaStateSwitcher::GetCrntState() == ApaStateType::SUCCESS_9 && ApaStateSwitcher::GetCount()  >= 60)
                {
                    ApaEventManager::SetExit(ApaExitType::SUCCESS_1);
                }
                else
                {
                    // No event update logic implemented yet.
                }
                // ApaEventManager::SetActvInhibited(ApaActvIhbtType::NONE_0);
                // ApaEventManager::SetGuidance(ApaGuidanceType::AUTO_5);
                // ApaEventManager::SetGuidanceInhibited(ApaGuidanceIhbtType::NONE_0);
                // ApaEventManager::SetPause(ApaPauseType::NONE_0);
                // ApaEventManager::SetSuccess(ApaSuccessType::DATA_VALID_1);
                // ApaEventManager::SetFail(ApaFailType::NONE_0);
                // ApaEventManager::SetExit(ApaExitType::NONE_0);
            }
            else
            {
                // No event update logic implemented yet.
            }
        }
    };
}