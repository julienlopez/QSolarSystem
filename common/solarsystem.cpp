#include "solarsystem.hpp"

SolarSystem::SolarSystem()
{
}

void SolarSystem::add(Body body)
{
    m_bodies.push_back(std::move(body));
}

Body::length_t SolarSystem::longestDistanceFromTheCenter() const
{
    auto it = std::max_element(m_bodies.cbegin(), m_bodies.cend(), [](const Body& b1, const Body& b2){
        return b1.position().norm2() < b2.position().norm2();
    });
    assert(it != m_bodies.cend());
    return it->position().norm();
}
