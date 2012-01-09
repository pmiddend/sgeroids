#ifndef SGEROIDS_MODEL_CALLBACKS_CHANGE_THRUST_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_CHANGE_THRUST_HPP_INCLUDED

#include <sgeroids/model/callbacks/change_thrust_function.hpp>
#include <fcppt/function/object.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function::object<callbacks::change_thrust_function>
change_thrust;
}
}
}

#endif
