#pragma once

#include "point2d.h"

namespace structure
{
template <typename T, typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
class Point3D : public Point2D<T>
{
private:
    T z_{static_cast<T>(0)};
public:
    Point3D(T x = static_cast<T>(0), T y = static_cast<T>(0), T z = static_cast<T>(0)) : Point2D<T>(x, y), z_(z)
    {

    }
    Point3D(const Point2D<T>& point, T z = static_cast<T>(0)) : Point2D<T>(point), z_(z)
    {

    }
    Point3D(const Point3D&) = default;
    Point3D& operator=(const Point3D&) = default;
    Point3D(Point3D&&) = default;
    Point3D& operator=(Point3D&&) = default;
public:
    const T& GetZ() const noexcept
    {
        return z_;
    }
    T& GetZ() noexcept
    {
        return z_;
    }
    void SetZ(T z = static_cast<T>(0))
    {
        z_ = z;
    }
public:
    template <typename U, typename = typename std::enable_if_t<std::is_base_of_v<Point3D, std::decay_t<U>>>>
    T DistOfChebyshev(U && point) const noexcept
    {
        return std::max(std::max(std::abs(Point2D<T>::GetX() - point.GetX()), std::abs(Point2D<T>::GetY() - point.GetY())), std::abs(z_ - point.GetZ()));
    }
    template <typename U, typename = typename std::enable_if_t<std::is_base_of_v<Point3D, std::decay_t<U>>>>
    T DistOfManhattan(U && point) const noexcept
    {
        return std::abs(Point2D<T>::GetX() - point.GetX()) + std::abs(Point2D<T>::GetY() - point.GetY()) + std::abs(z_ - point.GetZ());
    }
    template <typename U, typename = typename std::enable_if_t<std::is_base_of_v<Point3D, std::decay_t<U>>>>
    T DistOfEuclidean(U && point) const noexcept
    {
        return std::sqrt(std::pow((Point2D<T>::GetX() - point.GetX()), 2) + std::pow(Point2D<T>::GetY() - point.GetY(), 2) + std::pow(z_ - point.GetZ(), 2));
    }
};
};
