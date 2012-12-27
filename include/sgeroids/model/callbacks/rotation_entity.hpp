#ifndef SGEROIDS_MODEL_CALLBACKS_ROTATION_ENTITY_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_ROTATION_ENTITY_HPP_INCLUDED

#include <sgeroids/model/callbacks/rotation_entity_function.hpp>
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
std::function<callbacks::rotation_entity_function>
rotation_entity;
}
}
}

#endif
