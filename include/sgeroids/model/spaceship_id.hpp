#ifndef SGEROIDS_MODEL_SPACESHIP_ID_HPP_INCLUDED
#define SGEROIDS_MODEL_SPACESHIP_ID_HPP_INCLUDED

#include <sgeroids/model/entity_id.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sgeroids
{
namespace model
{
FCPPT_MAKE_STRONG_TYPEDEF(
	model::entity_id::value_type,
	spaceship_id);
}
}

#endif

