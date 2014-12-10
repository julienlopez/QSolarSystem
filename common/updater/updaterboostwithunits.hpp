#ifndef SOLARSYSTEMUPDATER_HPP
#define SOLARSYSTEMUPDATER_HPP

#include "solarsystem.hpp"

#include <boost/units/systems/si/acceleration.hpp>
#include <boost/units/systems/si/momentum.hpp>
#include <boost/units/systems/si/time.hpp>

namespace _impl_ {
    auto computeGravitationalConsant = []()
    {
        return 6.67384E-11 * boost::units::si::meter * boost::units::si::meter * boost::units::si::meter / boost::units::si::kilogram
                / boost::units::si::second / boost::units::si::second;
    };
}

class UpdaterBoostWithUnits
{
public:
    static const decltype(_impl_::computeGravitationalConsant()) gravitational_constant;
    using mass_container_t = std::vector<Body::mass_t>;
    using momentum_t = boost::units::quantity<boost::units::si::momentum>;
    using momentum_vector_t = Point3D<momentum_t>;
    using p_container_t = std::vector<momentum_vector_t>;
    using q_container_t = std::vector<Body::position_vector_t>;
    using dqdt_container_t = std::vector<Body::velocity_vector_t>;
    using acceleration_t = boost::units::quantity<boost::units::si::acceleration()>;
    using mass_acceleration_t = decltype(acceleration_t() * Body::mass_t());
    using mass_acceleration_vector_t = Point3D<mass_acceleration_t>;
    using dpdt_container_t = std::vector<mass_acceleration_vector_t>;

    struct solar_system_coor
    {
        const mass_container_t& m_masses;

        solar_system_coor(const mass_container_t& masses);

        /**
         * @brief operator ()
         * @param p
         * @param dqdt
         * @preconditions p.size() == m_masses.size()
         * @preconditions dqdt.size() == m_masses.size()
         */
        void operator()(const p_container_t& p, dqdt_container_t& dqdt) const;
    };

    struct solar_system_momentum
    {
        const mass_container_t& m_masses;

        solar_system_momentum(const mass_container_t& masses);

        /**
         * @brief operator ()
         * @param q
         * @param dqdt
         * @preconditions q.size() == m_masses.size()
         * @preconditions dqdt.size() == m_masses.size()
         */
        void operator()(const q_container_t& q, dpdt_container_t& dpdt) const;
    };

    UpdaterBoostWithUnits(SolarSystem& solarSystem);

    void update(boost::units::quantity<boost::units::si::time> dt, std::size_t nbPeriod = 1);

private:
    SolarSystem& m_solarSystem;

    mass_container_t extractMasses() const;

    q_container_t extractPositions() const;

    p_container_t extractMomentums() const;
};

#endif // SOLARSYSTEMUPDATER_HPP
