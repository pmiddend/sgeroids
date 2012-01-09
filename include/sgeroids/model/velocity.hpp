#ifndef SGEROIDS_MODEL_VELOCITY_HPP_INCLUDED
#define SGEROIDS_MODEL_VELOCITY_HPP_INCLUDED

#include <sgeroids/model/vector2.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sgeroids
{
namespace model
{
/**
\brief Specifies the velocity of an entity (asteroid uses this)
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	sgeroids::model::vector2,
	velocity);
}
}

#endif
