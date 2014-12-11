#include "body.hpp"

#include "updaterbasiceulerintegrationwithunits.hpp"

#include "solarsystem.hpp"

const std::string UpdaterBasicEulerIntegrationWithUnits::s_id = "UpdaterBasicEulerIntegrationWithUnits";

const decltype(_impl_::computeGravitationalConsant()) UpdaterBasicEulerIntegrationWithUnits::gravitational_constant = _impl_::computeGravitationalConsant();

UpdaterBasicEulerIntegrationWithUnits::UpdaterBasicEulerIntegrationWithUnits(SolarSystem& solarSystem):
    CRTP_Updater<UpdaterBasicEulerIntegrationWithUnits>(solarSystem)
{
    m_solarSystem.forEachBody([this](Body& body){ m_bodies.push_back(body);});
}

void UpdaterBasicEulerIntegrationWithUnits::impl_update(boost::units::quantity<boost::units::si::time> dt, std::size_t nbPeriod)
{
    assert(m_bodies.size() == m_solarSystem.count());
    for(std::size_t i = 0; i < nbPeriod; i++)
    {
        for(auto& b : m_bodies)
        {
            auto& body = b.get();
            const auto force = computeForce(body);
            const auto acceleration = force / body.mass();
            body.velocity() += acceleration * dt;
            body.position() += body.velocity() * dt;
        }
    }
}

Point3D<boost::units::quantity<boost::units::si::force>> UpdaterBasicEulerIntegrationWithUnits::computeForce(const Body& body)
{
    Point3D<boost::units::quantity<boost::units::si::force>> res = {0 * boost::units::si::newton};
    for(const auto& b : m_bodies)
    {
        if(&b.get() == &body) continue;
        const auto diff = b.get().position() - body.position();
        const auto d = diff.norm();
        const auto f = diff * ( gravitational_constant * body.mass() * b.get().mass() / d / d / d );
        res += f;
    }
    return res;
}
