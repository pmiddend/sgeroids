#ifndef SGEROIDS_MODEL_CALLBACKS_COLLIDE_PROJECTILE_ASTEROID_FUNCTION_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_COLLIDE_PROJECTILE_ASTEROID_FUNCTION_HPP_INCLUDED

#include <sgeroids/model/projectile_id.hpp>
#include <sgeroids/model/asteroid_id.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
void
collide_projectile_asteroid_function(
	model::projectile_id const &,
	model::asteroid_id const &);
}
}
}

#endif
