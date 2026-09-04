#pragma once

#include <iostream>
#include <mutex>
#include <utility>

namespace parking
{
    class ThreadSafeCout
    {
    public:
        template <typename T>
        ThreadSafeCout & operator<<(T && value)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            std::cout << std::forward<T>(value);
            return *this;
        }

    private:
        std::mutex mutex_;
    };

    static ThreadSafeCout thread_safe_cout;
}