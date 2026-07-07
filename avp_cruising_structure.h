#pragma once

#include <stdint.h>

class AvpCruisingRealTimeStatInfo
{
private:
    double distance_{0.0};
    uint64_t duration_{0};
};

class AvpCruisingEndingStatInfo
{
private:
    double distance_{0.0}; // 单位为米（S）
    uint64_t duration_{0}; // 单位为秒（S）
    uint8_t avoid_pedestrian_count_{0};
};