#ifndef UPDATERBASICEULERINTEGRATIONWITHUNITS_HPP
#define UPDATERBASICEULERINTEGRATIONWITHUNITS_HPP

#include "crtp_updater.hpp"

#include <point.hpp>

#include <boost/units/systems/si/force.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/mass.hpp>
#include <boost/units/systems/si/volume.hpp>
#include <boost/units/systems/si/area.hpp>

class Body;

namespace _impl_ {
    auto computeGravitationalConsant = []()
    {
//        return 6.67384E-11 * boost::units::si::cubic_meter / boost::units::si::kilogram
//                / boost::units::si::second / boost::units::si::second;
        return 6.67384E-11 * boost::units::si::newton * boost::units::si::square_meter / boost::units::si::kilogram / boost::units::si::kilogram;
    };
}


class UpdaterBasicEulerIntegrationWithUnits : public CRTP_Updater<UpdaterBasicEulerIntegrationWithUnits>
{
public:
    static const std::string s_id;

    static const decltype(_impl_::computeGravitationalConsant()) gravitational_constant;

    UpdaterBasicEulerIntegrationWithUnits(SolarSystem& solarSystem);

    virtual ~UpdaterBasicEulerIntegrationWithUnits() = default;

private:
    std::vector<std::reference_wrapper<Body>> m_bodies;

    void impl_update(boost::units::quantity<boost::units::si::time> dt, std::size_t nbPeriod) override;

    Point3D<boost::units::quantity<boost::units::si::force>> computeForce(const Body& body);
};

#endif // UPDATERBASICEULERINTEGRATION_HPP
