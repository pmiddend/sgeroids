#ifndef SGEROIDS_MODEL_LOCAL_CALLBACKS_INSERT_PROJECTILE_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_CALLBACKS_INSERT_PROJECTILE_HPP_INCLUDED

#include <sgeroids/model/local/callbacks/insert_projectile_function.hpp>
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
fcppt::function::object<local::callbacks::insert_projectile_function>
insert_projectile;
}
}
}
}

#endif
