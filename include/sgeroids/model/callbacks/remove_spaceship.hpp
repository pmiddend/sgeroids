#ifndef SGEROIDS_MODEL_CALLBACKS_REMOVE_SPACESHIP_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_REMOVE_SPACESHIP_HPP_INCLUDED

#include <sgeroids/model/callbacks/remove_spaceship_function.hpp>
#include <fcppt/function_impl.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function<sgeroids::model::callbacks::remove_spaceship_function>
remove_spaceship;
}
}
}

#endif

