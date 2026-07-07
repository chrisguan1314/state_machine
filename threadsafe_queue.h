#pragma once

#include <queue>
#include <mutex>
#include <memory>
#include <iostream>
#include <type_traits>
#include <condition_variable>

template <typename T>
class threadsafe_queue
{
public: 
    using DataType = T;
private:
    std::queue<DataType> queue_;
    mutable std::mutex mtx_;
    std::condition_variable cv_;
public:
    threadsafe_queue() noexcept = default;
    // 这个函数有待优化
    template <typename U, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<U>, std::decay_t<DataType>>>>
    void push(U && value)
    {
        {
            std::lock_guard<std::mutex> lck(mtx_);
            queue_.push(std::forward<U>(value));
            if (queue_.size() > 1)
            {
                std::cerr << "There are too many messages unhandle! size : " << queue_.size() << std::endl;
            }
        }
        cv_.notify_one();
    }
    void wait_and_pop(DataType & value)
    {
        std::unique_lock<std::mutex> lck(mtx_);
        cv_.wait(lck, [this]{return !queue_.empty();});
        value = std::move(queue_.front());
        queue_.pop();
    }
    std::shared_ptr<DataType> wait_and_pop()
    {
        std::unique_lock<std::mutex> lck(mtx_);
        cv_.wait(lck, [this]{return !queue_.empty();});
        std::shared_ptr<DataType> res = std::make_shared<DataType>(std::move(queue_.front()));
        queue_.pop();
        return res;
    }
    std::shared_ptr<DataType> wait_for_and_pop()
    {
        std::unique_lock<std::mutex> lck(mtx_);
        cv_.wait_for(lck, [this]{return !queue_.empty();});
        std::shared_ptr<DataType> res = std::make_shared<DataType>(std::move(queue_.front()));
        queue_.pop();
        return res;
    }
    bool try_pop(DataType & value)
    {
        std::unique_lock<std::mutex> lck(mtx_);
        if (queue_.empty())
        {
            return false;
        }
        else
        {
            value = std::move(queue_.front());
            queue_.pop();
            return true;
        }
    }
    std::shared_ptr<DataType> try_pop()
    {
        std::unique_lock<std::mutex> lck(mtx_);
        if (queue_.empty())
        {
            return std::make_shared<DataType>(nullptr);
        }
        else
        {
            std::shared_ptr<DataType> res = std::make_shared<DataType>(std::move(queue_.front()));
            queue_.pop();
            return res;
        }
    }
    bool empty() const noexcept
    {
        std::unique_lock<std::mutex> lck(mtx_);
        return queue_.empty();
    }  
    bool size() const noexcept
    {
        std::unique_lock<std::mutex> lck(mtx_);
        return queue_.size();
    }   
};