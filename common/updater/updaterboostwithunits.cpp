#include "updaterboostwithunits.hpp"

#include <boost/numeric/odeint.hpp>

const decltype(_impl_::computeGravitationalConsant()) UpdaterBoostWithUnits::gravitational_constant = _impl_::computeGravitationalConsant();

UpdaterBoostWithUnits::solar_system_coor::solar_system_coor(const mass_container_t& masses):
    m_masses(masses)
{}

void UpdaterBoostWithUnits::solar_system_coor::operator()(const p_container_t& p, dqdt_container_t& dqdt) const
{
    assert(p.size() == m_masses.size());
    assert(dqdt.size() == m_masses.size());
    const auto n = m_masses.size();
    for(size_t i=0 ; i<n ; ++i)
        dqdt[i] = p[i] / m_masses[i];
}

UpdaterBoostWithUnits::solar_system_momentum::solar_system_momentum(const mass_container_t& masses):
    m_masses(masses)
{}

void UpdaterBoostWithUnits::solar_system_momentum::operator()(const q_container_t& q, dpdt_container_t& dpdt) const
{
    assert(q.size() == m_masses.size());
    assert(dpdt.size() == m_masses.size());
    const size_t n = q.size();
    for(size_t i=0 ; i<n ; ++i)
    {
//        const auto null_mass_acceleration = .0 * boost::units::si::meters_per_second_squared * boost::units::si::kilogram;
        dpdt[i] = mass_acceleration_vector_t{/*null_mass_acceleration*/};
        for(size_t j=0 ; j<i ; ++j)
        {
            const auto diff = q[j] - q[i];
            const auto d = diff.norm();
            const auto res = diff * ( gravitational_constant * m_masses[i] * m_masses[j] / d / d / d );
            dpdt[i] += res;
            dpdt[j] -= res;

        }
    }
}

UpdaterBoostWithUnits::UpdaterBoostWithUnits(SolarSystem& solarSystem):
    m_solarSystem(solarSystem)
{}

void UpdaterBoostWithUnits::update(boost::units::quantity<boost::units::si::time> dt, std::size_t nbPeriod)
{
    using stepper_type = boost::numeric::odeint::symplectic_rkn_sb3a_mclachlan<q_container_t, p_container_t>;

    const auto masses = extractMasses();
    auto p = extractMomentums();
    auto q = extractPositions();

    boost::numeric::odeint::integrate_n_steps(
            stepper_type(),
            std::make_pair(solar_system_coor(masses), solar_system_momentum(masses)),
            std::make_pair(std::ref(q), std::ref(p)),
            0.0*boost::units::si::second, dt, nbPeriod /*, streaming_observer(cout)*/);
}

auto UpdaterBoostWithUnits::extractMasses() const -> mass_container_t
{
    mass_container_t res;
    std::size_t i = 0;
    m_solarSystem.forEachBody([&res, &i](const Body& b){ res[i++] = b.mass(); });
    return res;
}

auto UpdaterBoostWithUnits::extractPositions() const -> q_container_t
{
    q_container_t res;
    std::size_t i = 0;
    m_solarSystem.forEachBody([&res, &i](const Body& b){ res[i++] = b.position(); });
    return res;
}

auto UpdaterBoostWithUnits::extractMomentums() const -> p_container_t
{
    p_container_t res;
    std::size_t i = 0;
    m_solarSystem.forEachBody([&res, &i](const Body& b){ res[i++] = b.velocity() * b.mass(); });
    return res;
}
