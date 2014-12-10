#ifndef UPDATERFACTORY_HPP
#define UPDATERFACTORY_HPP

#include "iupdater.hpp"

#include <utils/factory.hpp>

#include <memory>

using up_updater_t = std::unique_ptr<iUpdater>;
using UpdaterFactory = utils::Factory<up_updater_t, std::string, std::function<up_updater_t(SolarSystem&)>>;

#endif // UPDATERFACTORY_HPP
