#pragma

#include <type_traits>
#include <cmath>

namespace structure
{
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
    template <typename U, typename = typename std::enable_if_t<std::is_base_of_v<Point2D, std::decay_t<U>>>>
    T DistOfChebyshev(U && point) const noexcept
    {
        return std::max(std::abs(x_ - std::forward<U>(point).GetX()), std::abs(y_ - std::forward<U>(point).GetY()));
    }
    template <typename U, typename = typename std::enable_if_t<std::is_base_of_v<Point2D, std::decay_t<U>>>>
    T DistOfManhattan(U && point) const noexcept
    {
        return std::abs(x_ - std::forward<U>(point).GetX()) + std::abs(y_ - std::forward<U>(point).GetY());
    }
    template <typename U, typename = typename std::enable_if_t<std::is_base_of_v<Point2D, std::decay_t<U>>>>
    T DistOfEuclidean(U && point) const noexcept
    {
        return std::sqrt(std::pow((x_ - std::forward<U>(point).GetX()), 2) + std::pow(y_ - std::forward<U>(point).GetY()));
    }
};
};

