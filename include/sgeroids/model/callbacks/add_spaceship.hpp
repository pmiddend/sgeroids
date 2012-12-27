#ifndef SGEROIDS_MODEL_CALLBACKS_ADD_SPACESHIP_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_ADD_SPACESHIP_HPP_INCLUDED

#include <sgeroids/model/callbacks/add_spaceship_function.hpp>
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
std::function<callbacks::add_spaceship_function>
add_spaceship;
}
}
}

#endif
