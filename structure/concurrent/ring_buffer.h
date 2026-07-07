#pragma once

#include <vector>
#include <mutex>
#include <memory>
#include <type_traits>
#include <condition_variable>

namespace concurrent
{

template<typename T, std::size_t N = 100>
class ring_buffer
{
public:
    // capacity：有效最大容量，内部会多开辟1个空位用来判满
    explicit ring_buffer() : buffer_(N + 1), read_idx_(0), write_idx_(0)
    {}

    // 阻塞写入：队列满则等待有空位
    template<typename U, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<U>, std::decay_t<T>>>>
    void push(U && item)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        // 等待直到缓冲区不满
        not_full_.wait(lock, [this]() { return !is_full(); });
        buffer_[write_idx_] = std::forward<U>(item);
        write_idx_ = (write_idx_ + 1) % buffer_.size();   
        lock.unlock();
        not_empty_.notify_one();
    }

    // 非阻塞写入，成功返回true，满了直接返回false
    template<typename U, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<U>, std::decay_t<T>>>>
    bool try_push(U && item)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (is_full())
        {
            return false;
        }
        buffer_[write_idx_] = std::forward<U>(item);
        write_idx_ = (write_idx_ + 1) % buffer_.size();
        not_empty_.notify_one();
        return true;
    }

    template<typename U, typename Rep, typename Period, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<U>, std::decay_t<T>>>>
    bool try_push_for(U && item, std::chrono::duration<Rep, Period> timeout)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        // 等待直到缓冲区不满
        if (not_full_.wait_for(lock, timeout, [this]() { return !is_full(); }))
        {
            buffer_[write_idx_] = std::forward<U>(item);
            write_idx_ = (write_idx_ + 1) % buffer_.size();

            lock.unlock();
            not_empty_.notify_one();
            return true;
        }
        else
        {
            return false;
        }
    }

    // 阻塞读取：队列为空则等待有数据
    void pop(T& out)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        not_empty_.wait(lock, [this]() { return !is_empty(); });

        out = buffer_[read_idx_];
        read_idx_ = (read_idx_ + 1) % buffer_.size();

        lock.unlock();
        not_full_.notify_one();
    }
    std::shared_ptr<T> pop()
    {
        std::unique_lock<std::mutex> lock(mtx_);
        not_empty_.wait(lock, [this]() { return !is_empty(); });

        std::shared_ptr<T> data = std::make_shared<T>(std::move(buffer_[read_idx_]));
        read_idx_ = (read_idx_ + 1) % buffer_.size();
        lock.unlock();
        not_full_.notify_one();
        return data;
    }

    // 非阻塞读取，有数据返回true，空返回false
    bool try_pop(T& out)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (is_empty())
        {
            return false;
        }
        out = buffer_[read_idx_];
        read_idx_ = (read_idx_ + 1) % buffer_.size();
        not_full_.notify_one();
        return true;
    }

    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (is_empty())
        {
            return nullptr;
        }
        std::shared_ptr<T> data = std::make_shared<T>(std::move(buffer_[read_idx_]));
        read_idx_ = (read_idx_ + 1) % buffer_.size();
        not_full_.notify_one();
        return data;
    }

    template<typename Rep, typename Period>
    bool try_pop_for(T& out, std::chrono::duration<Rep, Period> timeout)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        if (not_empty_.wait_for(lock, timeout, [this]() { return !is_empty(); }))
        {
            out = buffer_[read_idx_];
            read_idx_ = (read_idx_ + 1) % buffer_.size();
            lock.unlock();
            not_full_.notify_one();
            return true;
        }
        else
        {
            return false;
        }
    }

    template<typename Rep, typename Period>
    std::shared_ptr<T> try_pop_for(std::chrono::duration<Rep, Period> timeout)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        if (not_empty_.wait_for(lock, timeout, [this]() { return !is_empty(); }))
        {
            std::shared_ptr<T> data = std::make_shared<T>(std::move(buffer_[read_idx_]));
            read_idx_ = (read_idx_ + 1) % buffer_.size();

            lock.unlock();
            not_full_.notify_one();
            return data;
        }
        else
        {
            return nullptr;
        }
    }

    // 获取当前元素个数
    size_t size() const
    {
        std::lock_guard<std::mutex> lock(mtx_);
        return (write_idx_ - read_idx_ + buffer_.size()) % buffer_.size();
    }

    // 最大可用容量
    size_t capacity() const
    {
        return buffer_.size() - 1;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mtx_);
        return is_empty();
    }

    bool full() const
    {
        std::lock_guard<std::mutex> lock(mtx_);
        return is_full();
    }

private:
    bool is_empty() const
    {
        return read_idx_ == write_idx_;
    }

    bool is_full() const
    {
        return (write_idx_ + 1) % buffer_.size() == read_idx_;
    }

    std::vector<T> buffer_;
    size_t read_idx_;
    size_t write_idx_;

    mutable std::mutex mtx_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
};

};
