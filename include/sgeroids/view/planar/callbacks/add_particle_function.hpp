#ifndef SGEROIDS_VIEW_PLANAR_CALLBACKS_ADD_PARTICLE_FUNCTION_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_CALLBACKS_ADD_PARTICLE_FUNCTION_HPP_INCLUDED

#include <sgeroids/view/planar/position.hpp>
#include <sgeroids/view/planar/particle/velocity.hpp>
#include <sgeroids/view/planar/particle/lifespan.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
namespace callbacks
{
typedef
void
add_particle_function(
	planar::position const &_position,
	planar::particle::velocity const &_velocity,
	planar::particle::lifespan const &_lifespan);
}
}
}
}

#endif
