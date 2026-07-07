#pragma once

#include "structure.h"

#include <array>
#include <stdint.h>

// 主要用于处理所有回调中的输入数据
// 对于一个状态机的输入而言，从输入来源分类，可以分为：车机、MCU、算法模块
// 但如果对这些原始接口数据进行一层抽象，就可以将某些数据的变化抽象成事件（Event）
// 当然可以对事件进行一个标准化和规范化的分类，以下是一些基础事件类型
// 打开（open）
// 关闭/退出（Exit）
// 激活（Active）
// 暂停（Suspend）
// 中断（Terminate）

#include <shared_mutex>

#include "avp_cruising_event.h"
#include "avp_cruising_operation.h"

class AvpCruisingInput
{
private:
    std::shared_ptr<AvpCruisingEvent> event_{nullptr};
    mutable std::shared_mutex event_rw_mtx_;
    std::shared_ptr<AvpCruisingOperation> operation_{nullptr};
    mutable std::shared_mutex operation_rw_mtx_;
public:
    std::shared_ptr<AvpCruisingEvent> GetEvent() const noexcept
    {
        std::shared_lock<std::shared_mutex> lck(event_rw_mtx_);
        return event_;
    }
    std::shared_ptr<AvpCruisingOperation> GetOperation() const noexcept
    {
        std::shared_lock<std::shared_mutex> lck(operation_rw_mtx_);
        return operation_;
    }
    void SetEvent(const AvpCruisingEvent& event)
    {
        // 其实这里并不适合运用共享锁    
        std::lock_guard<std::shared_mutex> lck(event_rw_mtx_);
        event_ = std::make_shared<AvpCruisingEvent>(event);
    }
    void SetOperation(const AvpCruisingOperation& operation)
    {
        std::lock_guard<std::shared_mutex> lck(operation_rw_mtx_);
        operation_ = std::make_shared<AvpCruisingOperation>(operation);
    }
};