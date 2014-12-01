#ifndef POINT_HPP
#define POINT_HPP

#include <array>
#include <cassert>
#include <numeric>

template<class T, std::size_t DIM>
class Point
{
public:
    using value_type = T;
    using value_squared_type = decltype(T() * T());

    Point() = delete;
//    {
//        std::fill(m_values.begin(), m_values.end(), {});
//    }

//    template<class ... Args>
//    Point(Args&&... args): m_values(std::forward<Args>(args)...)
//    {}

    Point(const T& t)
    {
        std::fill(m_values.begin(), m_values.end(), t);
    }

    Point(typename std::initializer_list<T> values)
    {
        assert(values.size() == DIM && "wrong number of arguments passed to construct Point");
        std::size_t pos = 0;
        for(auto it = values.begin(); it != values.end(); ++it, pos++)
        {
            m_values[pos] = *it;
        }
    }

    Point(const Point&) = default;
    Point(Point&&) = default;


    Point& operator=(const Point&) = default;
    Point& operator=(Point&&) = default;

    const T& x() const
    {
        static_assert(DIM > 0, "");
        return m_values[0];
    }

    const T& y() const
    {
        static_assert(DIM > 1, "");
        return m_values[1];
    }

    const T& z() const
    {
        static_assert(DIM > 2, "");
        return m_values[2];
    }

    const T& operator[](std::size_t i) const
    {
        assert(i < DIM);
        return m_values[i];
    }

    T& operator[](std::size_t i)
    {
        assert(i < DIM);
        return m_values[i];
    }

    value_squared_type norm2() const
    {
        return std::inner_product(m_values.cbegin(), m_values.cend(), m_values.cbegin(), value_squared_type());
    }

    T norm() const
    {
        return sqrt(norm2());
    }

    Point& operator -=(const Point& p)
    {
        for(std::size_t i = 0; i < m_values.size(); ++i)
            m_values[i] -= p.m_values[i];
        return *this;
    }

    /**
     * \brief multiplication by a scalar
     */
    template<class U>
    Point<decltype(T() * U()), DIM> operator*(U u) const
    {
        Point<decltype(T() * U()), DIM> res{decltype(T() * U())()};
        for(std::size_t i = 0; i < DIM; ++i)
            res[i] *= u;
        return res;
    }

    /**
     * \brief division by a scalar
     */
    template<class U>
    Point<decltype(T() / U()), DIM> operator/(U u) const
    {
        Point<decltype(T() / U()), DIM> res{decltype(T() / U())()};
        for(std::size_t i = 0; i < DIM; ++i)
            res[i] /= u;
        return res;
    }

private:
    using container_t = std::array<T, DIM>;

    container_t m_values;
};

template<class T, std::size_t DIM>
Point<T, DIM> operator-(Point<T, DIM> p1, const Point<T, DIM>& p2)
{
    p1 -= p2;
    return p1;
}

template<class T> using Point3D = Point<T, 3>;

#endif // POINT_HPP
