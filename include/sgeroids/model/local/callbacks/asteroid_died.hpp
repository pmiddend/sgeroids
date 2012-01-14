#ifndef SGEROIDS_MODEL_LOCAL_CALLBACKS_ASTEROID_DIED_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_CALLBACKS_ASTEROID_DIED_HPP_INCLUDED

#include <sgeroids/model/local/callbacks/asteroid_died_function.hpp>
#include <fcppt/function/object.hpp>

namespace sgeroids
{
namespace model
{
namespace local
{
namespace callbacks
{
typedef
fcppt::function::object<callbacks::asteroid_died_function>
asteroid_died;
}
}
}
}

#endif
