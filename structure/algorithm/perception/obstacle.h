#pragma once

#include "..\common.h"

#include <vector>
#include <stdint.h>
#include <type_traits>

namespace structure
{
namespace perception
{
enum class ObstacleType : uint8_t
{
    UNKNOWN_0,
};

template <typename T>
class Obstacle
{
public:
    using Position = structure::Postion3D<T>;
    using Timestamp = structure::Timestamp;
private:
    Timestamp timestamp_;
    UUID id_{0};
    ObstacleType type_{ObstacleType::UNKNOWN_0};
    Position position_;
public:
    // template<typename T1, typename T2, typename T3, 
    // typename = typename std::enable_if_t<std::is_same_v<std::decay_t<T1>, Timestamp>>, 
    // typename = typename std::enable_if_t<std::is_same_v<std::decay_t<T2>, Position>>, 
    // typename = typename std::enable_if_t<std::is_same_v<std::decay_t<T3>, PredictPath>>>
    // Obstacle(T1 && timestamp = std::declval<T1>(), UUID id = 0, ObstacleType type = ObstacleType::UNKNOWN_0, bool is_dynamic = false, T2 && position = std::declval<T2>(), T3 && path = std::declval<T3>()) 
    // // timestamp_(std::forward<T1>(timestamp)), 
    // // id_(id),
    // // type_(type),
    // // dynamic_flag_(is_dynamic),
    // // position_(std::forward<T2>(position)),
    // // predict_path_(std::forward<T3>(path))
    // {

    // }
public:
    const Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }
    UUID GetID() const noexcept
    {
        return id_;
    }
    ObstacleType GetType() const noexcept
    {
        return type_;
    }
    const Position& GetPosition() const noexcept
    {
        return position_;
    }
    
public:
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<U>, Timestamp>>>
    void SetTimestamp(U && timestamp) noexcept
    {
        timestamp_ = std::forward<U>(timestamp);
    }
    void SetID(UUID id = 0) noexcept
    {
        id_ = id;
    }
    void SetType(ObstacleType type = ObstacleType::UNKNOWN_0) noexcept
    {
        type_ = type;
    }
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<U>, Position>>>
    void SetPosition(U && position) noexcept
    {
        position_ = std::forward<U>(position);
    }
    
};
};
};