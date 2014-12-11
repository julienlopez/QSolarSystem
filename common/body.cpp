#include "body.hpp"

#include <iostream>

boost::units::quantity<boost::units::si::length> sqrt(const decltype(boost::units::quantity<boost::units::si::length>()*boost::units::quantity<boost::units::si::length>())& l2)
{
    return sqrt(l2.value()) * boost::units::si::meter;
}

Body::Body(std::string name_, const mass_t& mass_, const length_t& meanRadius_, const position_vector_t& position_, const velocity_vector_t& velocity_):
    m_name(std::move(name_)), m_mass(mass_), m_meanRadius(meanRadius_), m_position(position_), m_velocity(velocity_)
{}

const std::string& Body::name() const
{
    return m_name;
}

auto Body::mass() const -> const mass_t&
{
    return m_mass;
}

auto Body::meanRadius() const -> const length_t&
{
    return m_meanRadius;
}

auto Body::position() const -> const position_vector_t&
{
    return m_position;
}

auto Body::velocity() const -> const velocity_vector_t&
{
    return m_velocity;
}

auto Body::position() -> position_vector_t&
{
    return m_position;
}

auto Body::velocity() -> velocity_vector_t&
{
    return m_velocity;
}

std::ostream& operator<<(std::ostream& o, const Body& body)
{
    o << std::fixed;// << std::setprecision(30);
    o << body.name() << " :\n";
    o << "Mass: " << body.mass().value() << "kg" << std::endl;
    o << "Mean Radius: " << body.meanRadius().value() << "m" << std::endl;
    o << "Position: " << body.position() << std::endl;
    o << "velocity: " << body.velocity() << std::endl;
    return o;
}

std::ostream& operator<<(std::ostream& o, const Body::position_vector_t& point)
{
    o << "{" << point.x().value() << ", " << point.y().value() << ", " << point.z().value() << "}";
    return o;
}

std::ostream& operator<<(std::ostream& o, const Body::velocity_vector_t& point)
{
    o << "{" << point.x().value() << ", " << point.y().value() << ", " << point.z().value() << "}";
    return o;
}
