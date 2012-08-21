#ifndef SGEROIDS_MODEL_CALLBACKS_SCORE_CHANGE_FUNCTION_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_SCORE_CHANGE_FUNCTION_HPP_INCLUDED

#include <sgeroids/model/score.hpp>
#include <sgeroids/model/spaceship_id.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
void
score_change_function(
	model::spaceship_id const &,
	model::score const &);
}
}
}

#endif
