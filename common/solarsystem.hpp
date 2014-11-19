#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include "body.hpp"

class SolarSystem : private utils::noncopiable
{
public:
    SolarSystem();

    void add(Body body);

private:
    using container_t = std::vector<Body>;

    container_t m_bodies;
};

#endif // SOLARSYSTEM_HPP
