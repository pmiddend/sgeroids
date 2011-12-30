#ifndef SGEROIDS_MODEL_CALLBACKS_ADD_SPACESHIP_FUNCTION_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_ADD_SPACESHIP_FUNCTION_HPP_INCLUDED

#include <sgeroids/model/entity_id.hpp>
#include <sgeroids/model/player_name.hpp>
#include <sgeroids/model/radius.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
void
add_spaceship_function(
	model::entity_id const &,
	model::radius const &,
	model::player_name const &);
}
}
}

#endif
