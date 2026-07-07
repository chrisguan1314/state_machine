#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>

class ThreadPool 
{
public:
    // 构造：创建 n 个工作线程
    explicit ThreadPool(size_t threadNum) : stop_(false) 
    {
        for (size_t i = 0; i < threadNum; ++i) 
        {
            workers_.emplace_back([this]() {
                while (true) 
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx_);
                        // 等待有任务或者线程池停止
                        cond_.wait(lock, [this]() { return stop_ || !tasks_.empty(); });

                        // 停止且任务队列为空，退出线程
                        if (stop_ && tasks_.empty()) 
                        {
                            return;
                        }

                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    task(); // 执行任务
                }
            });
        }
    }

    // 提交任意可调用对象，返回 future 获取返回值
    template<typename Func, typename... Args>
    auto submit(Func&& func, Args&&... args)
    {
        using ReturnType = decltype(func(args...));
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
        );

        std::future<ReturnType> res = task->get_future();
        {
            std::lock_guard<std::mutex> lock(mtx_);
            if (stop_) 
            {
                throw std::runtime_error("ThreadPool has stopped, cannot submit task");
            }
            tasks_.emplace([task]() { (*task)(); });
        }
        cond_.notify_one(); // 唤醒一个工作线程
        return res;
    }

    // 析构：优雅关闭线程池
    ~ThreadPool() 
    {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            stop_ = true;
        }
        cond_.notify_all(); // 唤醒所有等待线程

        // 等待所有工作线程执行完毕
        for (auto& worker : workers_) 
        {
            if (worker.joinable()) 
            {
                worker.join();
            }
        }
    }

    // 禁止拷贝与移动
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

private:
    std::vector<std::thread> workers_;                // 工作线程数组
    std::queue<std::function<void()>> tasks_;         // 任务队列（缓冲区）
    std::mutex mtx_;
    std::condition_variable cond_;
    std::atomic<bool> stop_;                          // 线程池停止标记
};