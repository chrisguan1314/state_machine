#pragma once

#include <stack>
#include <mutex>
#include <memory>
#include <exception>

// 在C++中，怎样创建用户自定义异常：继承于std::exception
// 并对what虚函数进行重写
// 对于这种简单的数据结构，可以考虑直接用struct，不需要用class
struct empty_stack : public std::exception
{
    const char* what() const noexcept
    {
        return "empty stack";
    }
};

template <typename T>
class threadsafe_stack
{
private:
    std::stack<T> stack_;
    mutable std::mutex mtx_;
public:
    threadsafe_stack() noexcept = default;
    threadsafe_stack(const threadsafe_stack& other) 
    {
        // 我其实有点不明白，为啥这里可以直接访问other的私有变量呢
        std::lock_guard<std::mutex> lck(other.mtx_);
        stack_ = other.stack_;
    }
    threadsafe_stack& operator=(const threadsafe_stack& other) = delete;
    threadsafe_stack(threadsafe_stack&& other) 
    {
        std::lock_guard<std::mutex> lck(other.mtx_);
        stack_ = std::move(other.stack_);
    }
    threadsafe_stack& operator=(threadsafe_stack&& other) = delete;
    void push(T new_value)
    {
        std::lock_guard<std::mutex> lck(mtx_);
        stack_.push(new_value);
    }
    bool empty() const noexcept
    {
        std::lock_guard<std::mutex> lck(mtx_);
        return stack_.empty();
    }
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lck(mtx_);
        if (stack_.empty())
        {
            throw empty_stack();
        }
        else
        {
            std::shared_ptr<T> res = std::make_shared<T>(std::move(stack_.top()));
            stack_.pop();
            return res;
        }
    }
    void pop(T & value)
    {
        std::lock_guard<std::mutex> lck(mtx_);
        if (stack_.empty())
        {
            throw empty_stack();
        }
        else
        {
            value = std::move(stack_.top());
            stack_.pop();
        }
    }
};
