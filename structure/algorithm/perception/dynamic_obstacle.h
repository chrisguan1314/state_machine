#pragma once

#include "obstacle.h"

namespace structure
{
namespace perception
{

template<typename T>
class DynamicObstacle : public Obstacle<T>
{
public:
    using PredictPath = std::vector<structure::PathPoint<T>>;
private:
    PredictPath predict_path_;
public:
    const PredictPath& GetPredictPath() const noexcept
    {
        return predict_path_;
    }
public:
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<U>, PredictPath>>>
    void SetPredictPath(U && path) noexcept
    {
        predict_path_ = std::forward<U>(path);
    }
};

};
};