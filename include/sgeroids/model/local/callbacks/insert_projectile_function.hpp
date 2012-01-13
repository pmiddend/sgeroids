#ifndef SGEROIDS_MODEL_LOCAL_CALLBACKS_INSERT_PROJECTILE_FUNCTION_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_CALLBACKS_INSERT_PROJECTILE_FUNCTION_HPP_INCLUDED

#include <sgeroids/model/position.hpp>
#include <sgeroids/model/rotation.hpp>

namespace sgeroids
{
namespace model
{
namespace local
{
namespace callbacks
{
typedef
void
insert_projectile_function(
	model::position const &,
	model::rotation const &);
}
}
}
}

#endif
