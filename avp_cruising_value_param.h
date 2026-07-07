#pragma once

#include <stdint.h>

class AvpCruisingValueParam
{
private:
    uint8_t success_page_remain_time_{3};
    uint8_t recovery_interrupt_ramain_time_{30};
};