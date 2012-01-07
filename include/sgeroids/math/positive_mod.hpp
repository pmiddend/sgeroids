#ifndef SGEROIDS_MATH_POSITIVE_MOD_HPP_INCLUDED
#define SGEROIDS_MATH_POSITIVE_MOD_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>

namespace sgeroids
{
namespace math
{
template<typename V>
typename
boost::enable_if
<
	boost::is_integral<V>,
	V
>::type
positive_mod(
	V const a,
	V const b)
{
	return (a % b + b) % b;
}

}
}

#endif
