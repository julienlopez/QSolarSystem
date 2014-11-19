    #include "solarsystem.hpp"

SolarSystem::SolarSystem()
{
}

void SolarSystem::add(Body body)
{
    m_bodies.push_back(std::move(body));
}
