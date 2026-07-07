#pragma once

#include <type_traits>
#include <vector>
#include <cmath>

// 这个时间戳类的设计之后要仔细考虑一下
// 其肯定是要基于chrono库中提供的接口进行设计
// 但是这个时间戳类具体要提供哪些接口还要考虑一下
// TODO 
class Timestamp {};

// 这里涉及到两个分开的知识点：1、C++模板 2、模板元编程
// type_traits本身就是一个C++中支持模板元编程的库
// 这里主要用到以下几个模板类：std::enable_if<>, std::is_floating_point<>, std::is_integral<>
// 这里还涉及到一个知识点：C++中模版参数也可以不显示声明，因为本身也不会被用到，其一般也只被用来限制模板参数的有效范围
template <typename T, typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
class Point2D
{
private:
    T x_{static_cast<T>(0)};
    T y_{static_cast<T>(0)};
public:
    Point2D(T x = static_cast<T>(0), T y = static_cast<T>(0)) noexcept : x_(x), y_(y) {}
    Point2D(const Point2D&) noexcept = default;
    Point2D& operator=(const Point2D&) noexcept = default;
    Point2D(Point2D&&) noexcept = default;
    Point2D& operator=(Point2D&&) noexcept = default;
    ~Point2D() noexcept = default;
public:
    const T& GetX() const noexcept
    {
        return x_;
    }
    const T& GetY() const noexcept
    {
        return y_;
    }
    T& GetX() noexcept
    {
        return x_;
    }
    T& GetY() noexcept
    {
        return y_;
    }
    void SetX(T x = static_cast<T>(0)) noexcept
    {
        x_ = x;
    }
    void SetY(T y = static_cast<T>(0)) noexcept
    {
        y_ = y;
    }
public:
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<U>, Point2D>>>
    T DistOfChebyshev(U && point) const noexcept
    {
        return std::max(std::abs(x_ - std::forward<U>(point).GetX()), std::abs(y_ - std::forward<U>(point).GetY()));
    }
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<U>, Point2D>>>
    T DistOfManhattan(U && point) const noexcept
    {
        return std::abs(x_ - std::forward<U>(point).GetX()) + std::abs(y_ - std::forward<U>(point).GetY());
    }
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<U>, Point2D>>>
    T DistOfEuclidean(U && point) const noexcept
    {
        return std::sqrt(std::pow((x_ - std::forward<U>(point).GetX()), 2) + std::pow(y_ - std::forward<U>(point).GetY()));
    }
};

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
    T DistOfChebyshev(const Point3D& point) const noexcept
    {
        return std::max(std::max(std::abs(Point2D<T>::GetX() - point.GetX()), std::abs(Point2D<T>::GetY() - point.GetY())), std::abs(z_ - point.GetZ()));
    }
    T DistOfManhattan(const Point3D& point) const noexcept
    {
        return std::abs(Point2D<T>::GetX() - point.GetX()) + std::abs(Point2D<T>::GetY() - point.GetY()) + std::abs(z_ - point.GetZ());
    }
    T DistOfEuclidean(const Point3D& point) const noexcept
    {
        return std::sqrt(std::pow((Point2D<T>::GetX() - point.GetX()), 2) + std::pow(Point2D<T>::GetY() - point.GetY(), 2) + std::pow(z_ - point.GetZ(), 2));
    }
};

template <typename T>
using Postion = Point3D<T>;

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
    T DistOfChebyshev(const Point6D& point) const noexcept
    {
        return std::max(std::max(std::abs(Point3D<T>::GetX() - point.GetX()), std::abs(Point3D<T>::GetY() - point.GetY())), std::abs(Point3D<T>::GetZ() - point.GetZ()));
    }
    T DistOfManhattan(const Point6D& point) const noexcept
    {
        return std::abs(Point3D<T>::GetX() - point.GetX()) + std::abs(Point3D<T>::GetY() - point.GetY()) + std::abs(Point3D<T>::GetZ() - point.GetZ());
    }
    T DistOfEuclidean(const Point6D& point) const noexcept
    {
        return std::sqrt(std::pow((Point3D<T>::GetX() - point.GetX()), 2) + std::pow(Point3D<T>::GetY() - point.GetY(), 2) + std::pow(Point3D<T>::GetZ() - point.GetZ(), 2));
    }
};