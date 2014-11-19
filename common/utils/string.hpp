#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <iosfwd>
#include <string>
#include <vector>

#include "namespace_utils.hpp"

BEGIN_NAMESPACE_UTILS

namespace string
{
    using string_container_t = std::vector<std::string>;

    /**
     * @brief streamToLines extract each non empty line in the stream and put them into a container
     * @param in the stream to extract the lines from
     * @return the collection of lines extracted from the stream
     * @pre in is valid
     */
    string_container_t streamToLines(std::istream& in);

    bool contains(const std::string& str, const std::string& token);

    std::string trimAllSpaces(std::string str);

    bool startsWith(const std::string& str, const std::string& token);

    string_container_t split(std::string str, const std::string& token);
}

END_NAMESPACE_UTILS

#endif
