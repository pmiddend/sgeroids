#ifndef SGEROIDS_MODEL_CALLBACKS_ROTATION_ENTITY_FUNCTION_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_ROTATION_ENTITY_FUNCTION_HPP_INCLUDED

#include <sgeroids/model/entity_id.hpp>
#include <sgeroids/model/rotation.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
void
rotation_entity_function(
	model::entity_id const &,
	model::rotation const &);
}
}
}

#endif
