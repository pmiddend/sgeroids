#ifndef SGEROIDS_MODEL_CALLBACKS_ADD_PROJECTILE_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_ADD_PROJECTILE_HPP_INCLUDED

#include <sgeroids/model/callbacks/add_projectile_function.hpp>
#include <fcppt/function/object.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function::object<callbacks::add_projectile_function>
add_projectile;
}
}
}

#endif
