#ifndef SGEROIDS_MODEL_CALLBACKS_CHANGE_THRUST_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_CHANGE_THRUST_HPP_INCLUDED

#include <sgeroids/model/callbacks/change_thrust_function.hpp>
#include <fcppt/function_impl.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function<callbacks::change_thrust_function>
change_thrust;
}
}
}

#endif
