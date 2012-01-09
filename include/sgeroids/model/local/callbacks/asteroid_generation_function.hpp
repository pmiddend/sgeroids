#ifndef SGEROIDS_MODEL_LOCAL_CALLBACKS_ASTEROID_GENERATION_FUNCTION_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_CALLBACKS_ASTEROID_GENERATION_FUNCTION_HPP_INCLUDED

#include <sgeroids/model/position.hpp>
#include <sgeroids/model/rotation.hpp>
#include <sgeroids/model/rotation_direction.hpp>
#include <sgeroids/model/radius.hpp>
#include <sgeroids/model/velocity.hpp>

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
asteroid_generation_function(
	model::position const &,
	model::rotation const &,
	model::rotation_direction const &,
	model::radius const &,
	model::velocity const &);
}
}
}
}

#endif
