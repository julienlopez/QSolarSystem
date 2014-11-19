#include "utils/string.hpp"

#include <cassert>
#include <istream>

#include <boost/algorithm/string.hpp>

BEGIN_NAMESPACE_UTILS

auto string::streamToLines(std::istream& in) -> string::string_container_t
{
    assert(in);
    string_container_t lignes;
	std::string tmp;
    while(std::getline(in, tmp))
	{
		if(!tmp.empty())
		{
			lignes.push_back(tmp);
		}
	}
	return lignes;
}

bool string::contains(const std::string& str, const std::string& token)
{
    if(token.size() > str.size()) return false;
    const auto pos = str.find(token);
    return pos < str.size();
}

std::string string::trimAllSpaces(std::string str)
{
    while(!str.empty() && std::isspace(str.front())) str.erase(0, 1);
    while(!str.empty() && std::isspace(str.back())) str.pop_back();

    for(std::string::size_type pos = 0; pos < str.size(); pos++)
    {
        if(std::isspace(str[pos]))
        {
            const auto p2 = pos + 1;
            while(std::isspace(str[p2]) && p2 < str.size())
                str.erase(p2, 1);
        }
    }
    return str;
}

bool string::startsWith(const std::string& str, const std::string& token)
{
    if(token.size() > str.size()) return false;
    return str.find(token) == 0;
}

auto string::split(std::string str, const std::string& token) -> string_container_t
{
    string_container_t res;
    return boost::algorithm::split(res, str, boost::algorithm::is_any_of(" "));
}

END_NAMESPACE_UTILS
