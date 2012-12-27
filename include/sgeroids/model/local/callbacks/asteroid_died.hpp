#ifndef SGEROIDS_MODEL_LOCAL_CALLBACKS_ASTEROID_DIED_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_CALLBACKS_ASTEROID_DIED_HPP_INCLUDED

#include <sgeroids/model/local/callbacks/asteroid_died_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>

namespace sgeroids
{
namespace model
{
namespace local
{
namespace callbacks
{
typedef
std::function<callbacks::asteroid_died_function>
asteroid_died;
}
}
}
}

#endif
