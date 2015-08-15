#ifndef SGEROIDS_MODEL_CALLBACKS_ADD_ASTEROID_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_ADD_ASTEROID_HPP_INCLUDED

#include <sgeroids/model/callbacks/add_asteroid_function.hpp>
#include <fcppt/function_impl.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function<callbacks::add_asteroid_function>
add_asteroid;
}
}
}

#endif
