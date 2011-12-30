#ifndef SGEROIDS_MODEL_CALLBACKS_ADD_SPACESHIP_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_ADD_SPACESHIP_HPP_INCLUDED

#include <sgeroids/model/callbacks/add_spaceship_function.hpp>
#include <fcppt/function/object.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function::object<callbacks::add_spaceship_function>
add_spaceship;
}
}
}

#endif
