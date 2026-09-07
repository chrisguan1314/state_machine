#pragma once

#include "../../../state_machine_event_base.h"

namespace parking
{
/**
 * @brief APA 状态机的事件对象。
 *
 * @details
 * 该类型将通用 StateMachineEventBase 绑定到 APA 功能域，供 ApaInputer
 * 创建并传递给输入基类。实际的 APA 事件分类与标志管理由 ApaEventManager
 * 及其 ParkingEventManager 基类负责。
 */
class ApaEvent final : public StateMachineEventBase
{
};
}