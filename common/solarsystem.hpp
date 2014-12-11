#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include "body.hpp"

class SolarSystem : private utils::noncopiable
{
public:
    SolarSystem();

    void add(Body body);

    template<class FCT>
    void forEachBody(FCT fct) const
    {
        std::for_each(m_bodies.cbegin(), m_bodies.cend(), fct);
    }

    template<class FCT>
    void forEachBody(FCT fct)
    {
        std::for_each(m_bodies.begin(), m_bodies.end(), fct);
    }

    Body::length_t longestDistanceFromTheCenter() const;

    std::size_t count() const;

private:
    using container_t = std::vector<Body>;

    container_t m_bodies;
};

#endif // SOLARSYSTEM_HPP
