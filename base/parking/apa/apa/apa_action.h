#pragma once

#include "../../../state_machine_action_base.h"

namespace parking
{
/**
 * @brief APA 状态机的动作对象。
 *
 * @details
 * 该类型将通用 StateMachineActionBase 绑定到 APA 功能域，供 ApaOutputer
 * 在创建时传递给输出基类。当前不新增 APA 专用动作状态；后续需要持久化
 * 动作数据时可在此扩展。
 */
class ApaAction final : public StateMachineActionBase
{
};
}