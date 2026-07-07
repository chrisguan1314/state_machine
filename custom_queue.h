#pragma once

#include <memory>

template <typename T>
class custom_queue
{
private:
    struct Node
    {
        std::shared_ptr<T> data_{nullptr};
        std::unique_ptr<Node> next_{nullptr};
        Node(T data) : data_(std::make_shared<T>(data)), next_(nullptr) {}
    };
private:
    std::unique_ptr<Node> head_{nullptr};
    Node * tail_{nullptr};
public:
    custom_queue() noexcept : head_(new Node(0)), tail_(head_.get())
    {

    }
    custom_queue(const custom_queue&) = delete;
    custom_queue& operator=(const custom_queue&) = delete;
    std::shared_ptr<T> try_pop()
    {
        if (!head_)
        {
            return nullptr;
        }
        else
        {
            std::shared_ptr<T> res = std::make_shared<T>(std::move(head_->data_));
            head_ = std::move(head_->next_);
            tail_ = head_ ? tail_ : nullptr;
            return res;
        }
    }
    void push(T new_value)
    {
        std::shared_ptr<T> data = std::make_shared<T>(new_value);
        tail_->next_.reset(data.get());
        tail_ = tail_->next_;
    }
};