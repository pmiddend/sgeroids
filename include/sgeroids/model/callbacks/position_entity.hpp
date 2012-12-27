#ifndef SGEROIDS_MODEL_CALLBACKS_POSITION_ENTITY_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_POSITION_ENTITY_HPP_INCLUDED

#include <sgeroids/model/callbacks/position_entity_function.hpp>
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
std::function<callbacks::position_entity_function>
position_entity;
}
}
}

#endif
