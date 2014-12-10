#include "updaterboostnounits.hpp"

#include <boost/numeric/odeint.hpp>

const std::string UpdaterBoostNoUnits::s_id = "UpdaterBoostNoUnits";

const double UpdaterBoostNoUnits::gravitational_constant = 6.67384E-11;

UpdaterBoostNoUnits::solar_system_coor::solar_system_coor(const mass_container_t& masses):
    m_masses(masses)
{}

void UpdaterBoostNoUnits::solar_system_coor::operator()(const container_t& p, container_t& dqdt) const
{
    assert(p.size() == m_masses.size());
    assert(dqdt.size() == m_masses.size());
    const auto n = m_masses.size();
    for(size_t i=0 ; i<n ; ++i)
        dqdt[i] = p[i] / m_masses[i];
}

UpdaterBoostNoUnits::solar_system_momentum::solar_system_momentum(const mass_container_t& masses):
    m_masses(masses)
{}

void UpdaterBoostNoUnits::solar_system_momentum::operator()(const container_t& q, container_t& dpdt) const
{
    assert(q.size() == m_masses.size());
    assert(dpdt.size() == m_masses.size());
    const size_t n = q.size();
    for(size_t i=0 ; i<n ; ++i)
    {
        dpdt[i] = Point3D<double>{0};
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

UpdaterBoostNoUnits::UpdaterBoostNoUnits(SolarSystem& solarSystem): CRTP_Updater<UpdaterBoostNoUnits>(solarSystem)
{}

void UpdaterBoostNoUnits::impl_update(boost::units::quantity<boost::units::si::time> dt, std::size_t nbPeriod)
{
    using stepper_type = boost::numeric::odeint::symplectic_rkn_sb3a_mclachlan<container_t, container_t>;

    const auto masses = extractMasses();
    auto p = extractMomentums();
    auto q = extractPositions();

    boost::numeric::odeint::integrate_n_steps(
            stepper_type(),
            std::make_pair(solar_system_coor(masses), solar_system_momentum(masses)),
            std::make_pair(std::ref(q), std::ref(p)),
            0.0, dt.value(), nbPeriod /*, streaming_observer(cout)*/);
}

auto UpdaterBoostNoUnits::extractMasses() const -> mass_container_t
{
    mass_container_t res;
    std::size_t i = 0;
    m_solarSystem.forEachBody([&res, &i](const Body& b){ res[i++] = b.mass().value(); });
    return res;
}

auto UpdaterBoostNoUnits::extractPositions() const -> container_t
{
    container_t res;
    std::size_t i = 0;
    m_solarSystem.forEachBody([&res, &i](const Body& b){ res[i++] = {b.position().x().value(), b.position().y().value(), b.position().z().value()}; });
    return res;
}

auto UpdaterBoostNoUnits::extractMomentums() const -> container_t
{
    container_t res;
    std::size_t i = 0;
    m_solarSystem.forEachBody([&res, &i](const Body& b){
        res[i++] = {b.velocity().x().value() * b.mass().value(), b.velocity().y().value() * b.mass().value(), b.velocity().z().value() * b.mass().value()};
    });
    return res;
}
