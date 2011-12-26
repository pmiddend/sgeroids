#ifndef SGEROIDS_MODEL_CALLBACKS_DESTROY_ASTEROID_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_DESTROY_ASTEROID_HPP_INCLUDED

#include <sgeroids/model/callbacks/destroy_asteroid_function.hpp>
#include <fcppt/function/object.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function::object<callbacks::destroy_asteroid_function>
destroy_asteroid;
}
}
}

#endif
