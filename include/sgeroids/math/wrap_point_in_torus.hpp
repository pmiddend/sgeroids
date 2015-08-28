#ifndef SGEROIDS_MATH_WRAP_POINT_IN_TORUS_HPP_INCLUDED
#define SGEROIDS_MATH_WRAP_POINT_IN_TORUS_HPP_INCLUDED

#include <fcppt/make_int_range_count.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>


namespace sgeroids
{
namespace math
{
template<typename T,fcppt::math::size_type N,typename S>
fcppt::math::vector::static_<T,N>
wrap_point_in_torus(
	fcppt::math::vector::object<T,N,S> p,
	fcppt::math::box::object<T,N> const &b)
{
	for(
		auto const i
		:
		fcppt::make_int_range_count(
			N
		)
	)
	{
		T const
			left =
				b.pos()[i],
			right =
				left + b.size()[i];

		if(p[i] > right)
			p[i] =
				static_cast<T>(
					left + (p[i] - right));
		else if (p[i] < left)
			p[i] =
				static_cast<T>(
					right - (left - p[i]));
	}

	return p;
}
}
}

#endif
