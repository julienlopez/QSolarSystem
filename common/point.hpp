#ifndef POINT_HPP
#define POINT_HPP

#include <array>
#include <cassert>

template<class T, std::size_t DIM>
class Point
{
public:
    Point() = delete;
//    {
//        std::fill(m_values.begin(), m_values.end(), {});
//    }

//    template<class ... Args>
//    Point(Args&&... args): m_values(std::forward<Args>(args)...)
//    {}

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

private:
    using container_t = std::array<T, DIM>;

    container_t m_values;
};

template<class T> using Point3D = Point<T, 3>;

#endif // POINT_HPP
