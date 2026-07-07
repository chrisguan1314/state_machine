#pragma once

#include <stdint.h>

struct AvmValueParam
{
public:
    uint8_t success_page_remain_time_{3}; // 功能完成页面的保持时间，单位为秒（S）
    uint8_t interrupt_recovery_remain_time_{30}; // 可恢复中断升级成不可恢复中断时间，单位为秒（S）
};