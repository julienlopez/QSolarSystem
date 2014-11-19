#ifndef BODYPARSER_HPP
#define BODYPARSER_HPP

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

#include <utils/noninstantiable.hpp>

#include "body.hpp"

class BodyParser : private utils::noninstantiable
{
public:
    static Body parse(std::string name, std::istream& in);

    /**
     * @brief parseFromFile parse the file data/name.dat to create the according body
     * @param fileName
     * @return
     * @throw std::invalid_argument if the file doesn't exist in the data folder
     */
    static Body parseFromFile(std::string name);

private:
    using string_container_t = std::vector<std::string>;

    static std::string createFileName(const std::string& name);

    /**
     * @brief parseLineWithTwoValues
     * @param line
     * @return
     * @post res.size() == 2
     */
    static std::map<std::string, std::string> parseLineWithTwoValues(std::string line);

    static std::pair<std::string, std::string> parsePairKeyValue(const std::string& line);

    static Body::mass_t findMass(const string_container_t& lines);

    static Body::length_t findRadius(const string_container_t& lines);

    static Body::position_vector_t findPosition(const string_container_t& lines);

    static Body::velocity_vector_t findVelocity(const string_container_t& lines);

    static double parsePowerOfTen(std::string str);
};

#endif // BODYPARSER_HPP
