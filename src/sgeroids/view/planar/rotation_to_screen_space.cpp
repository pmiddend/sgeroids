#include <sgeroids/view/planar/rotation_to_screen_space.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <fcppt/math/deg_to_rad.hpp>

sgeroids::view::planar::rotation const
sgeroids::view::planar::rotation_to_screen_space(
	model::rotation const &_r)
{
	return
		planar::rotation(
			fcppt::math::deg_to_rad(
				static_cast<float>(
					_r.get()) /
				static_cast<float>(
					sgeroids::math::unit_magnitude())));
}
