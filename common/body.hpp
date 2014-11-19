#ifndef BODY_HPP
#define BODY_HPP

#include <string>

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/mass.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/velocity.hpp>

#include <utils/noncopiable.hpp>

#include "point.hpp"

class Body : private utils::noncopiable
{
public:
    using mass_t = boost::units::quantity<boost::units::si::mass>;
    using length_t = boost::units::quantity<boost::units::si::length>;
    using velocity_t = boost::units::quantity<boost::units::si::velocity>;
    using position_vector_t = Point3D<length_t>;
    using velocity_vector_t = Point3D<velocity_t>;

    Body(std::string name_, const mass_t& mass_, const length_t& meanRadius_, const position_vector_t& position_, const velocity_vector_t& velocity_);

    const std::string& name() const;

    const mass_t& mass() const;

    const length_t& meanRadius() const;

    const position_vector_t& position() const;

    const velocity_vector_t& velocity() const;

private:
    const std::string m_name;
    const mass_t m_mass;
    const length_t m_meanRadius;

    position_vector_t m_position;
    velocity_vector_t m_velocity;
};

std::ostream& operator<<(std::ostream& o, const Body& body);

std::ostream& operator<<(std::ostream& o, const Body::position_vector_t& point);
std::ostream& operator<<(std::ostream& o, const Body::velocity_vector_t& point);

#endif // BODY_HPP
