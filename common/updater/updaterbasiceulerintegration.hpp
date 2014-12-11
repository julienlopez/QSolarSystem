#ifndef UPDATERBASICEULERINTEGRATION_HPP
#define UPDATERBASICEULERINTEGRATION_HPP

#include "crtp_updater.hpp"

#include <point.hpp>

class Body;

class UpdaterBasicEulerIntegration : public CRTP_Updater<UpdaterBasicEulerIntegration>
{
public:
    static const std::string s_id;

    static const double gravitational_constant;

    UpdaterBasicEulerIntegration(SolarSystem& solarSystem);

    virtual ~UpdaterBasicEulerIntegration() = default;

private:
    std::vector<std::reference_wrapper<Body>> m_bodies;

    void impl_update(boost::units::quantity<boost::units::si::time> dt, std::size_t nbPeriod) override;

    Point3D<double> computeForce(const Body& body);
};

#endif // UPDATERBASICEULERINTEGRATION_HPP
