#ifndef SGEROIDS_MODEL_CALLBACKS_COLLIDE_PROJECTILE_ASTEROID_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_COLLIDE_PROJECTILE_ASTEROID_HPP_INCLUDED

#include <sgeroids/model/callbacks/collide_projectile_asteroid_function.hpp>
#include <fcppt/function/object.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function::object<callbacks::collide_projectile_asteroid_function>
collide_projectile_asteroid;
}
}
}

#endif
