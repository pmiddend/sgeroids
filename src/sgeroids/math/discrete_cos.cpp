#include <sgeroids/math/discrete_cos.hpp>
#include <sgeroids/math/lookup_table.hpp>
#include <fcppt/math/ceil_div.hpp>
#include <cstdlib>

int
sgeroids::math::discrete_cos(
	int const x)
{
	x += 90;

	std::size_t const index =
		x < 0
		?
			(fcppt::math::ceil_div(x,360u)*360u - x)
		:
			x % 360;

	return lookup_table[index];
}
