#include "updaterbasiceulerintegration.hpp"

#include "solarsystem.hpp"

#include <boost/units/systems/si/acceleration.hpp>

const std::string UpdaterBasicEulerIntegration::s_id = "UpdaterBasicEulerIntegration";

const double UpdaterBasicEulerIntegration::gravitational_constant = 6.67384E-11;

UpdaterBasicEulerIntegration::UpdaterBasicEulerIntegration(SolarSystem& solarSystem):
    CRTP_Updater<UpdaterBasicEulerIntegration>(solarSystem)
{
    std::cout << "UpdaterBasicEulerIntegration::UpdaterBasicEulerIntegration()\n";
    m_solarSystem.forEachBody([this](Body& body){ m_bodies.push_back(body); });
}

namespace
{
    template<class T>
    Point3D<double> stripUnits(const Point3D<T>& p)
    {
        Point3D<double> res = {p.x().value(), p.y().value(), p.z().value()};
        return  res;
    }

    template<class T, class U>
    Point3D<T> addUnits(const Point3D<double>& p, U unit)
    {
        return Point3D<T> {{p.x() * unit, p.y() * unit, p.z() * unit}};
    }

    template<class T>
    std::ostream& operator<<(std::ostream& o, const Point3D<T>& p)
    {
        o << "{" << p.x() << ", " << p.y() << ", " << p.z() << "}";
        return o;
    }
}

void UpdaterBasicEulerIntegration::impl_update(boost::units::quantity<boost::units::si::time> dt, std::size_t nbPeriod)
{
    assert(m_bodies.size() == m_solarSystem.count());
    for(std::size_t i = 0; i < nbPeriod; i++)
    {
        for(auto& b : m_bodies)
        {
            auto& body = b.get();
            const auto force = computeForce(body);
            const auto acceleration = force / body.mass().value();
            const auto v = acceleration * dt.value();
            body.velocity() += addUnits<boost::units::quantity<boost::units::si::velocity>>(v, boost::units::si::meters_per_second);
            const auto p = v * dt.value();
            body.position() += addUnits<boost::units::quantity<boost::units::si::length>>(p, boost::units::si::meters);
        }
    }
}

Point3D<double> UpdaterBasicEulerIntegration::computeForce(const Body& body)
{
    Point3D<double> res = {0, 0, 0};
    for(const auto& b : m_bodies)
    {
        if(&b.get() == &body) continue;
        const Point3D<double> diff = stripUnits(b.get().position()) - stripUnits(body.position());
        const auto d = diff.norm();
        const Point3D<double> tmp = diff * (gravitational_constant * body.mass().value() * b.get().mass().value() / d / d / d);
        const auto f = tmp;
        res += f;
    }
    return res;
}
