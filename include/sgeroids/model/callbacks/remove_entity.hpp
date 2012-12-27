#ifndef SGEROIDS_MODEL_CALLBACKS_REMOVE_ENTITY_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_REMOVE_ENTITY_HPP_INCLUDED

#include <sgeroids/model/callbacks/remove_entity_function.hpp>
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
std::function<callbacks::remove_entity_function>
remove_entity;
}
}
}

#endif
