#pragma once

#include <stdint.h>
#include <string>
#include <atomic>
#include <iostream>
#include <type_traits>

struct ApaValueParam
{
private:
    std::filesystem::path apa_value_param_path_;
public:
    std::atomic<uint8_t> success_page_remain_time_{3}; // 功能完成页面的保持时间，单位为秒（S）
    std::atomic<uint8_t> interrupt_recovery_remain_time_{30}; // 可恢复中断升级成不可恢复中断时间，单位为秒（S）
public:
    template <typename T, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<T>, std::filesystem::path>>>
    ApaValueParam(T && path) : apa_value_param_path_(std::forward<T>(path))
    {
        std::cout << "Apa Value Param Path : " << apa_value_param_path_ << std::endl;
    }
};