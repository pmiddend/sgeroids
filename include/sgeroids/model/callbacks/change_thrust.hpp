#ifndef SGEROIDS_MODEL_CALLBACKS_CHANGE_THRUST_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_CHANGE_THRUST_HPP_INCLUDED

#include <sgeroids/model/callbacks/change_thrust_function.hpp>
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
std::function<callbacks::change_thrust_function>
change_thrust;
}
}
}

#endif
