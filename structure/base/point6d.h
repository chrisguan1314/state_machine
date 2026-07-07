#pragma once

#include "point3d.h"

namespace structure
{
template <typename T, typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
class Point6D : public Point3D<T>
{
private:
    T roll_{static_cast<T>(0)};
    T pitch_{static_cast<T>(0)};
    T yaw_{static_cast<T>(0)};
public:
    Point6D(T x = static_cast<T>(0), T y = static_cast<T>(0), T z = static_cast<T>(0), T roll = static_cast<T>(0), T pitch = static_cast<T>(0), T yaw = static_cast<T>(0)) : Point3D<T>(x, y, z), roll_(roll), pitch_(pitch), yaw_(yaw)
    {

    }
    Point6D(const Point3D<T>& point, T roll = static_cast<T>(0), T pitch = static_cast<T>(0), T yaw = static_cast<T>(0)) : Point3D<T>(point), roll_(roll), pitch_(pitch), yaw_(yaw)
    {

    }
    Point6D(const Point6D&) = default;
    Point6D& operator=(const Point6D&) = default;
    Point6D(Point6D&&) = default;
    Point6D& operator=(Point6D&&) = default;
public:
    const T& GetRoll() const noexcept
    {
        return roll_;
    }
    T& GetRoll() noexcept
    {
        return roll_;
    }
    
    const T& GetPitch() const noexcept
    {
        return pitch_;
    }
    T& GetPitch() noexcept
    {
        return pitch_;
    }
    
    const T& GetYaw() const noexcept
    {
        return yaw_;
    }
    T& GetYaw() noexcept
    {
        return yaw_;
    }
public:
    void SetPitch(T pitch = static_cast<T>(0))
    {
        pitch_ = pitch;
    }
    void SetRoll(T roll = static_cast<T>(0))
    {
        roll_ = roll;
    }
    void SetYaw(T yaw = static_cast<T>(0))
    {
        yaw_ = yaw;
    }
public:
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<U>, Point6D>>>
    T DistOfChebyshev(U && point) const noexcept
    {
        return Point3D<T>::DistOfChebyshev(point);
    }
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<U>, Point6D>>>
    T DistOfManhattan(U && point) const noexcept
    {
        return Point3D<T>::DistOfManhattan(point);
    }
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<U>, Point6D>>>
    T DistOfEuclidean(U && point) const noexcept
    {
        return Point3D<T>::DistOfEuclidean(point);
    }
};
};
