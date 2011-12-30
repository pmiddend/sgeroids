#ifndef SGEROIDS_VIEW_PLANAR_RADIUS_TO_SCREEN_SPACE_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_RADIUS_TO_SCREEN_SPACE_HPP_INCLUDED

#include <sgeroids/view/planar/radius.hpp>
#include <sgeroids/model/radius.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
planar::radius const
radius_to_screen_space(
	model::radius const &);
}
}
}

#endif
