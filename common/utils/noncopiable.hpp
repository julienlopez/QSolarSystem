#ifndef NONCOPIABLE_HPP
#define NONCOPIABLE_HPP

#include "namespace_utils.hpp"

BEGIN_NAMESPACE_UTILS

class noncopiable
{
protected:
	noncopiable() = default;

	noncopiable(const noncopiable&) = delete;

	noncopiable& operator=(const noncopiable&) = delete;

	noncopiable(noncopiable&&) = default;

	noncopiable& operator=(noncopiable&&) = default;
};

END_NAMESPACE_UTILS

#endif // NONCOPIABLE_HPP
