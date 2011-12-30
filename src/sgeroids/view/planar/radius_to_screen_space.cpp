#include <sgeroids/view/planar/radius.hpp>
#include <sgeroids/model/radius.hpp>

sgeroids::view::planar::radius const
sgeroids::view::planar::radius_to_screen_space(
	model::radius const &_r)
{
	return
		planar::radius(
			_r.get());
}
