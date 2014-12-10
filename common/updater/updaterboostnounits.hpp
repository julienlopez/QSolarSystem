#ifndef UPDATERBOOSTNOUNITS_HPP
#define UPDATERBOOSTNOUNITS_HPP

#include "solarsystem.hpp"
#include "crtp_updater.hpp"

class UpdaterBoostNoUnits : public CRTP_Updater<UpdaterBoostNoUnits>
{
public:
    static const std::string s_id;

    static const double gravitational_constant;
    using container_t = std::vector<Point3D<double>>;
    using mass_container_t = std::vector<double>;

    struct solar_system_coor
    {
        const mass_container_t& m_masses;

        solar_system_coor(const mass_container_t& masses);

        /**
         * @brief operator ()
         * @param p
         * @param dqdt
         * @preconditions p.size() == m_masses.size()
         * @preconditions dqdt.size() == m_masses.size()
         */
        void operator()(const container_t& p, container_t& dqdt) const;
    };

    struct solar_system_momentum
    {
        const mass_container_t& m_masses;

        solar_system_momentum(const mass_container_t& masses);

        /**
         * @brief operator ()
         * @param q
         * @param dqdt
         * @preconditions q.size() == m_masses.size()
         * @preconditions dqdt.size() == m_masses.size()
         */
        void operator()(const container_t& q, container_t& dpdt) const;
    };

    UpdaterBoostNoUnits(SolarSystem& solarSystem);

private:
    void impl_update(boost::units::quantity<boost::units::si::time> dt, std::size_t nbPeriod) override;

    mass_container_t extractMasses() const;

    container_t extractPositions() const;

    container_t extractMomentums() const;
};

#endif // SOLARSYSTEMUPDATER_HPP
