#pragma once

#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>
namespace concurrent
{

template <typename T>
class msg_queue
{
private:
    std::queue<T> queue_;
    std::mutex mtx_;
    std::condition_variable cv_;
public:
    msg_queue() = default;
    ~msg_queue() = default;
    msg_queue(const msg_queue&) = delete;
    msg_queue& operator=(const msg_queue&) = delete;
    msg_queue(msg_queue&&) = delete;
    msg_queue& operator=(msg_queue&&) = delete;
public:
    template<typename U, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<U>, T>>>
    void push(U && data)
    {
        {
            std::lock_guard<std::mutex> lck(mtx_);
            queue_.push(std::forward<U>(data));
        }
        cv_.notify_one();
    }
    std::shared_ptr<T> wait_pop()
    {
        std::unique_lock<std::mutex> lck(mtx_);
        cv_.wait(lck, [this]{ return !queue_.empty(); });
        std::shared_ptr<T> data = std::make_shared<T>(std::move(queue_.front()));
        queue_.pop();
        lck.unlock();
        return data;
    }
};

};
