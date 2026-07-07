#pragma once

#include <thread>
#include <memory>

namespace concurrent
{

class thread_guard
{
private:
    std::thread trd_;
public:
    thread_guard(std::thread && trd): trd_(std::move(trd)) {}
    template <typename Function, typename... Args>
    thread_guard(Function func, Args&&... args) : trd_(std::forward<Function>(func), std::forward<Args>(args)...) {}
    ~thread_guard()
    {
        if (trd_.joinable())
        {
            trd_.join();
        }
    }
    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
    thread_guard(thread_guard&&) = default;
    thread_guard& operator=(thread_guard&&) = default;
};

};
