#ifndef SGEROIDS_MODEL_CALLBACKS_POSITION_ENTITY_FUNCTION_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_POSITION_ENTITY_FUNCTION_HPP_INCLUDED

#include <sgeroids/model/entity_id.hpp>
#include <sgeroids/model/position.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
void
position_entity_function(
	model::entity_id const &,
	model::position const &);
}
}
}

#endif
