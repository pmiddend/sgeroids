#ifndef SGEROIDS_MODEL_POSITION_HPP_INCLUDED
#define SGEROIDS_MODEL_POSITION_HPP_INCLUDED

#include <sgeroids/model/vector2.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sgeroids
{
namespace model
{
/**
\brief Specifies the position of an entity
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	model::vector2,
	position);
}
}

#endif
