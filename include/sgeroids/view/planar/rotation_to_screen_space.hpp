#ifndef SGEROIDS_VIEW_PLANAR_ROTATION_TO_SCREEN_SPACE_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_ROTATION_TO_SCREEN_SPACE_HPP_INCLUDED

#include <sgeroids/view/planar/rotation.hpp>
#include <sgeroids/model/rotation.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
planar::rotation const
rotation_to_screen_space(
	model::rotation const &);
}
}
}

#endif
