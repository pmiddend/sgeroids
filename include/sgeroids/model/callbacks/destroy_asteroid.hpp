#ifndef SGEROIDS_MODEL_CALLBACKS_DESTROY_ASTEROID_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_DESTROY_ASTEROID_HPP_INCLUDED

#include <sgeroids/model/callbacks/destroy_asteroid_function.hpp>
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
std::function<callbacks::destroy_asteroid_function>
destroy_asteroid;
}
}
}

#endif
