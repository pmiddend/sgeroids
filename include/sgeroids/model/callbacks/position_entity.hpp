#ifndef SGEROIDS_MODEL_CALLBACKS_POSITION_ENTITY_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_POSITION_ENTITY_HPP_INCLUDED

#include <sgeroids/model/callbacks/position_entity_function.hpp>
#include <fcppt/function/object.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function::object<callbacks::position_entity_function>
position_entity;
}
}
}

#endif
