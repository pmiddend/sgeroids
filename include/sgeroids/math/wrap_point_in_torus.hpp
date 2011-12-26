#ifndef SGEROIDS_MATH_WRAP_POINT_IN_TORUS_HPP_INCLUDED
#define SGEROIDS_MATH_WRAP_POINT_IN_TORUS_HPP_INCLUDED

#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>

namespace sgeroids
{
namespace math
{
template<typename T,fcppt::math::size_type N,typename VN,typename S>
fcppt::math::vector::basic<T,VN,S> const
wrap_point_in_torus(
	fcppt::math::vector::basic<T,VN,S> p,
	fcppt::math::box::basic<T,N> const &b)
{
	typedef
	fcppt::math::vector::basic<T,VN,S>
	vector;

	typedef typename
	vector::size_type
	size_type;

	for(size_type i = 0; i < p.size(); ++i)
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
