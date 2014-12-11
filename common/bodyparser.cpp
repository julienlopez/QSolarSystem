#include "bodyparser.hpp"

#include <cassert>
#include <fstream>

#include <boost/filesystem.hpp>

#include <boost/algorithm/string.hpp>

#include <utils/string.hpp>

#include "body.hpp"

Body BodyParser::parse(std::string name, std::istream& in)
{
//    std::cout << "BodyParser::parse(" << name << ")" << std::endl;
    auto lines = utils::string::streamToLines(in);
//    std::cout << lines.size() << " lignes extraites:" << std::endl;
//    for(const auto& l : lines)
//        std::cout << l << std::endl;
    if(lines.empty()) throw std::runtime_error("No lines were parsed from the file");
    if(lines.front().find_first_not_of("*") != std::string::npos) throw std::runtime_error("The first line of the file is invalid");

    auto old_locale = std::setlocale(LC_NUMERIC, nullptr);
    std::setlocale(LC_NUMERIC, "en_US");

    auto mass = findMass(lines);
    auto radius = findRadius(lines);
    auto position = findPosition(lines);
    auto velocity = findVelocity(lines);

    std::setlocale(LC_NUMERIC, old_locale);

    return Body(std::move(name), mass, radius, position, velocity);
}

Body BodyParser::parseFromFile(std::string name)
{
    const auto fileName = createFileName(name);
    if(!boost::filesystem::exists(fileName))
    {
        throw std::invalid_argument("The file " + fileName + " doesn't exists");
    }

    std::ifstream file(fileName);
    assert(file);
    return parse(std::move(name), file);
}

std::string BodyParser::createFileName(const std::string& name)
{
    auto fileName = "../data/" + name + ".dat";
    boost::algorithm::to_lower(fileName);
    return fileName;
}

std::map<std::string, std::string> BodyParser::parseLineWithTwoValues(std::string line)
{
//    std::cout << "BodyParser::parseLineWithTwoValues(" << line << ")\n";
    std::map<std::string, std::string> res;

    auto pos = line.find('=');
    assert(pos < line.size());
    pos = line.find(' ', pos + 2);
    assert(pos < line.size());

    std::string first = line.substr(0, pos);
    std::string second = line.substr(pos + 1);

//    std::cout << "first = " << first << std::endl;
//    std::cout << "second = " << second << std::endl;

    res.insert(parsePairKeyValue(first));
    res.insert(parsePairKeyValue(second));

    assert(res.size() == 2);
    return res;
}

std::pair<std::string, std::string> BodyParser::parsePairKeyValue(const std::string& line)
{
//    std::cout << "BodyParser::parsePairKeyValue(" << line << "): " << line.size() << "\n";
    auto pos = line.find('=');
    if(pos == std::string::npos)
    {
        pos = line.find('~');
        if(pos == std::string::npos)
        {
            pos = line.find(':');
        }
    }
    assert(pos < line.size());
    const auto key = line.substr(0, pos);
    utils::string::trimAllSpaces(key);
    if(pos + 2 > line.size())
        return std::make_pair(key, "");
    return std::make_pair(key, line.substr(pos + 2));
}

Body::mass_t BodyParser::findMass(const string_container_t& lines)
{
    const std::string title = "Mass";
    auto it = std::find_if(lines.begin(), lines.end(), [&title](const std::string& line){ return utils::string::contains(line, title); });
    if(it == lines.end()) throw std::runtime_error("Unable to find the mass of the body in the file");
    auto str = utils::string::trimAllSpaces(*it);
    auto values = parseLineWithTwoValues(str);
    auto it_map = std::find_if(values.begin(), values.end(), [&title](const std::pair<std::string, std::string>& p) {
        return utils::string::startsWith(p.first, title + " ");
    });
    assert(it_map != values.end());
    auto scale = it_map->first.substr(5);
    while(!scale.empty() && scale[0] != '(')
    {
        scale.erase(0, 1);
    }
    scale.erase(0, 1);
    auto pos = scale.find(' ');
    assert(pos < scale.size());
    scale.erase(pos);
    auto multiplier = parsePowerOfTen(scale);
    return Body::mass_t(std::stod(it_map->second) * multiplier * boost::units::si::kilogram);
}

Body::length_t BodyParser::findRadius(const string_container_t& lines)
{
    std::string title = "Mean radius";
    auto it = std::find_if(lines.begin(), lines.end(), [&title](const std::string& line){ return utils::string::contains(line, title); });
    if(it == lines.end())
    {
        title = "Radius";
        it = std::find_if(lines.begin(), lines.end(), [&title](const std::string& line){ return utils::string::contains(line, title); });
        if(it == lines.end())
        {
            title = "Volumetric mean radius";
            it = std::find_if(lines.begin(), lines.end(), [&title](const std::string& line){ return utils::string::contains(line, title); });
            if(it == lines.end()) throw std::runtime_error("Unable to find the mean radius of the body in the file");
        }
    }
    auto str = utils::string::trimAllSpaces(*it);
    auto values = parseLineWithTwoValues(str);
    auto it_map = std::find_if(values.begin(), values.end(), [&title](const std::pair<std::string, std::string>& p) {
        return utils::string::startsWith(p.first, title + " ") || utils::string::startsWith(p.first, title);
    });
    assert(it_map != values.end());
    auto valueStr = it_map->second;
    auto value = std::stod(valueStr);
    if(utils::string::contains(valueStr, "(") && utils::string::contains(valueStr, ")"))
    {
        auto pos = valueStr.find('(');
        assert(pos < valueStr.size());
        auto multiplier = valueStr.substr(pos+1);
        multiplier.pop_back();
        valueStr = valueStr.substr(0, pos);
        if(utils::string::contains(multiplier, "^"))
        {
            value = std::stod(valueStr) * parsePowerOfTen(multiplier);
        }
    }
    return Body::length_t(value * 1000 * boost::units::si::meter);
}

Body::position_vector_t BodyParser::findPosition(const string_container_t& lines)
{
    auto it = std::find(lines.begin(), lines.end(), "$$SOE");
    if(it == lines.end()) throw std::runtime_error("Unable to find the position of the body in the file");
    ++it; ++it;
    assert(it != lines.end());
    auto str = utils::string::trimAllSpaces(*it);
    auto values = utils::string::split(str, " ");
    if(values.size() != 3)
    {
        throw std::runtime_error("Invalid position format");
    }
    return Body::position_vector_t{std::stod(values[0]) * 1000 * boost::units::si::meter, std::stod(values[1]) * 1000 * boost::units::si::meter, std::stod(values[2]) * 1000 * boost::units::si::meter};
}

Body::velocity_vector_t BodyParser::findVelocity(const string_container_t& lines)
{
    auto it = std::find(lines.begin(), lines.end(), "$$SOE");
    if(it == lines.end()) throw std::runtime_error("Unable to find the position of the body in the file");
    ++it; ++it; ++it;
    assert(it != lines.end());
    auto str = utils::string::trimAllSpaces(*it);
    auto values = utils::string::split(str, " ");
    if(values.size() != 3)
    {
        throw std::runtime_error("Invalid velocity format");
    }
    return Body::velocity_vector_t{std::stod(values[0]) * 1000 * boost::units::si::meters_per_second, std::stod(values[1]) * 1000 * boost::units::si::meters_per_second, std::stod(values[2]) * 1000 * boost::units::si::meters_per_second};
}

double BodyParser::parsePowerOfTen(std::string str)
{
    assert(utils::string::contains(str, "^"));
    auto pos = str.find('^');
    assert(pos < str.size());
    return pow(std::stod(str.substr(0, pos)), std::stod(str.substr(pos+1)));
}
