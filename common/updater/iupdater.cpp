#include "iupdater.hpp"

iUpdater::iUpdater(SolarSystem& solarSystem): m_solarSystem(solarSystem)
{}

std::string iUpdater::id() const
{
    return impl_id();
}

bool iUpdater::isRegistered() const
{
    return impl_isRegistered();
}

void iUpdater::update(boost::units::quantity<boost::units::si::time> dt, std::size_t nbPeriod)
{
    impl_update(dt, nbPeriod);
}
