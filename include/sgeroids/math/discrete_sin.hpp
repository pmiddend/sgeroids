#ifndef SGEROIDS_MATH_DISCRETE_SIN_HPP_INCLUDED
#define SGEROIDS_MATH_DISCRETE_SIN_HPP_INCLUDED

#include <sgeroids/math/degrees.hpp>

namespace sgeroids
{
namespace math
{
/**
\brief Calculates the discrete cosine, scaled by the unit magnitude
\param d The angle in nonscaled degrees (can be negative)
\see sgeroids::math::unit_magnitude
*/
int
discrete_sin(
	math::degrees const &d);
}
}

#endif
