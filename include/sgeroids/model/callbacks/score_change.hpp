#ifndef SGEROIDS_MODEL_CALLBACKS_SCORE_CHANGE_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_SCORE_CHANGE_HPP_INCLUDED

#include <sgeroids/model/callbacks/score_change_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
std::function<callbacks::score_change_function>
score_change;
}
}
}

#endif
