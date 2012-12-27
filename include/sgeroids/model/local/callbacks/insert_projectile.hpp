#ifndef SGEROIDS_MODEL_LOCAL_CALLBACKS_INSERT_PROJECTILE_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_CALLBACKS_INSERT_PROJECTILE_HPP_INCLUDED

#include <sgeroids/model/local/callbacks/insert_projectile_function.hpp>
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
std::function<local::callbacks::insert_projectile_function>
insert_projectile;
}
}
}
}

#endif
