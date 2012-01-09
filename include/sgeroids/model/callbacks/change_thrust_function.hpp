#ifndef SGEROIDS_MODEL_CALLBACKS_CHANGE_THRUST_FUNCTION_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_CHANGE_THRUST_FUNCTION_HPP_INCLUDED

#include <sgeroids/model/entity_id.hpp>
#include <sgeroids/model/thrust.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
void
change_thrust_function(
	model::entity_id const &,
	model::thrust const &);
}
}
}

#endif
