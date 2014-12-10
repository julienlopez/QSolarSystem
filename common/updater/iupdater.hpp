#ifndef IUPDATER_HPP
#define IUPDATER_HPP

#include <utils/noncopiable.hpp>

#include <boost/units/systems/si/time.hpp>
#include <boost/units/quantity.hpp>

class SolarSystem;

class iUpdater : private utils::noncopiable
{
public:
    std::string id() const;

    bool isRegistered() const;

    void update(boost::units::quantity<boost::units::si::time> dt, std::size_t nbPeriod = 1);

protected:
    iUpdater(SolarSystem& solarSystem);

    SolarSystem& m_solarSystem;

private:
    virtual std::string impl_id() const = 0;

    virtual bool impl_isRegistered() const = 0;

    virtual void impl_update(boost::units::quantity<boost::units::si::time> dt, std::size_t nbPeriod) = 0;
};

#endif // IUPDATER_HPP
