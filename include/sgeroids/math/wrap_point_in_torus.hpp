#ifndef SGEROIDS_MATH_WRAP_POINT_IN_TORUS_HPP_INCLUDED
#define SGEROIDS_MATH_WRAP_POINT_IN_TORUS_HPP_INCLUDED

#include <fcppt/use.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/vector/at_c.hpp>
#include <fcppt/math/vector/init.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>


namespace sgeroids
{
namespace math
{
template<typename T,fcppt::math::size_type N,typename S>
fcppt::math::vector::static_<T,N>
wrap_point_in_torus(
	fcppt::math::vector::object<T,N,S> const p,
	fcppt::math::box::object<T,N> const &b)
{
	return
		fcppt::math::vector::init<
			fcppt::math::vector::static_<T,N>
		>(
			[
				p,
				&b
			](
				auto const _index
			)
			{
				FCPPT_USE(
					_index
				);

				typedef
				decltype(
					_index
				)
				index;

				T const
					left{
						fcppt::math::vector::at_c<
							index::value
						>(
							b.pos()
						)
					},
					right{
						fcppt::math::vector::at_c<
							index::value
						>(
							b.max()
						)
					},
					x{
						fcppt::math::vector::at_c<
							index::value
						>(
							p
						)
					};

				if(
					x > right
				)
					return
						left + (x - right);

				if(
					x < left
				)
					return
						right - (left - x);

				return
					x;
			}
		);
}
}
}

#endif
