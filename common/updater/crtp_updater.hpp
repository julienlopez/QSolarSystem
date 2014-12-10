#ifndef CRTP_UPDATER_HPP
#define CRTP_UPDATER_HPP

#include "iupdater.hpp"
#include "updaterfactory.hpp"

#include <utils/make_unique.hpp>

template<class T>
class CRTP_Updater : public iUpdater
{
protected:
    CRTP_Updater(SolarSystem& solarSystem): iUpdater(solarSystem)
    {}

    virtual std::string impl_id() const override
    {
        return T::s_id;
    }

    virtual bool impl_isRegistered() const override
    {
        return s_registered;
    }

    static const bool s_registered;
};

template<class T>
const bool CRTP_Updater<T>::s_registered = UpdaterFactory::instance().registerProduct(
                T::s_id,
                [](SolarSystem& solarSystem) -> std::unique_ptr<iUpdater> { return utils::make_unique<T>(solarSystem); });

#endif // CRTP_UPDATER_HPP
