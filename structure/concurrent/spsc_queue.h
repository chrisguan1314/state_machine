#pragma once

#include <atomic>
#include <array>
#include <optional>
#include <stdint.h>

namespace concurrent
{

template<typename T, std::size_t Capacity = 16>
class SpscQueue
{
private:
    static_assert((Capacity & (Capacity - 1)) == 0, "The capacity of SpscQueue must be power of 2!");
    std::atomic<uint8_t> head_{0};
    std::atomic<uint8_t> tail_{0};
    std::atomic<uint8_t> size_{0};
    std::array<T, Capacity> buffer_;
public:
    bool push(const T& value)
    {
        const uint8_t tail = tail_.load(std::memory_order_acquire);
        const uint8_t next_tail = (tail_ + 1) & (Capacity - 1);
        if (next_tail == head_.load(std::memory_order_acquire))
        {
            return false;
        }
        else
        {
            buffer_[next_tail] = value;
            tail_.store(next_tail, std::memory_order_release);
            size_.fetch_add(1, std::memory_order_acq_rel);
            return true;
        }
    }
    bool pop(T & value)
    {
        const uint8_t head = head_.load(std::memory_order_acquire);
        if (head == tail_.load(std::memory_order_acquire))
        {
            return false;
        }
        else
        {
            value = buffer_[head];
            head_.store((head + 1) & (Capacity - 1), std::memory_order_release);
            size_.fetch_sub(1, std::memory_order_acq_rel);
            return true;
        }
    }
    std::optional<T> pop()
    {
        std::optional<T> res;
        const uint8_t head = head_.load(std::memory_order_acquire);
        if (head != tail_.load(std::memory_order_acquire))
        {
            res = std::make_optional(buffer_[head]);
            head_.store((head + 1) & (Capacity - 1), std::memory_order_release);
        }
        return res;
    }
    uint8_t size() const noexcept
    {
        return size_.load(std::memory_order_acquire);
    }
    bool empty() const noexcept
    {
        return (head_.load() == tail_.load());
    }
};

};
