#ifndef SGEROIDS_MODEL_CALLBACKS_REMOVE_ENTITY_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_REMOVE_ENTITY_HPP_INCLUDED

#include <sgeroids/model/callbacks/remove_entity_function.hpp>
#include <fcppt/function/object.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function::object<callbacks::remove_entity_function>
remove_entity;
}
}
}

#endif
