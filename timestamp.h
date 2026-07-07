#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <cstdint>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#elif __linux__ || __unix__
#include <unistd.h>
#endif

// 时间单位定义
enum class TimeUnit
{
    Second,      // 秒
    Millisecond, // 毫秒
    Microsecond, // 微秒
    Nanosecond   // 纳秒
};

class Timestamp
{
public:
    // 构造函数
    Timestamp() : m_microSec(0) {}
    explicit Timestamp(int64_t microSec) : m_microSec(microSec) {}

    // 获取当前时间戳（默认微秒）
    static Timestamp Now();

    // 获取当前时间戳，指定单位
    static Timestamp Now(TimeUnit unit);

    // 获取内部存储的微秒时间戳
    int64_t GetMicroSeconds() const { return m_microSec; }

    // 转换为指定单位时间戳数值
    int64_t ToValue(TimeUnit unit) const;

    // 转为标准 time_t (秒级时间戳)
    time_t ToTimeT() const;

    // 时间戳 -> 本地格式化字符串
    // fmt 默认: "%Y-%m-%d %H:%M:%S.%f" 带毫秒
    std::string ToString(const std::string& fmt = "%Y-%m-%d %H:%M:%S") const;

    // 仅输出日期
    std::string ToDateString() const;

    // 仅输出时间
    std::string ToTimeString() const;

    // 运算符重载：比较、加减
    bool operator<(const Timestamp& other) const;
    bool operator>(const Timestamp& other) const;
    bool operator==(const Timestamp& other) const;
    bool operator!=(const Timestamp& other) const;

    Timestamp operator+(int64_t microSec) const;
    Timestamp operator-(int64_t microSec) const;

    // 获取两个时间戳的时间差（返回微秒）
    int64_t DiffMicroSec(const Timestamp& other) const;

    // 静态休眠函数
    static void Sleep(int64_t val, TimeUnit unit = TimeUnit::Millisecond);

private:
    // 统一使用微秒作为内部存储基准，避免单位混乱
    int64_t m_microSec;
    // 1秒 = 1e6 微秒
    static constexpr int64_t kMicroSecPerSec = 1000000LL;
    static constexpr int64_t kMilliPerSec = 1000LL;
};

#endif // TIMESTAMP_H