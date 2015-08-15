#ifndef SGEROIDS_MODEL_CALLBACKS_DESTROY_ASTEROID_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_DESTROY_ASTEROID_HPP_INCLUDED

#include <sgeroids/model/callbacks/destroy_asteroid_function.hpp>
#include <fcppt/function_impl.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function<callbacks::destroy_asteroid_function>
destroy_asteroid;
}
}
}

#endif
