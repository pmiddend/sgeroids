#ifndef SGEROIDS_MODEL_LOCAL_CALLBACKS_ROTATION_ENTITY_NO_ID_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_CALLBACKS_ROTATION_ENTITY_NO_ID_HPP_INCLUDED

#include <sgeroids/model/local/callbacks/rotation_entity_no_id_function.hpp>
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
/**
\brief Used inside the entitys to send messages "from themselves" without them knowing their own id.

\see sgeroids::model::local::callbacks::position_entity_no_id
*/
typedef
std::function<callbacks::rotation_entity_no_id_function>
rotation_entity_no_id;
}
}
}
}

#endif
