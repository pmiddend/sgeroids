#ifndef SGEROIDS_MODEL_LOCAL_CALLBACKS_POSITION_ENTITY_NO_ID_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_CALLBACKS_POSITION_ENTITY_NO_ID_HPP_INCLUDED

#include <sgeroids/model/local/callbacks/position_entity_no_id_function.hpp>
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

Note that there is already a similar callback:
sgeroids::model::callbacks::position_entity which takes an id in addition to
the position. However, the <code>no_id</code> callback is used by an entity
itself to send a message about a position change. The entity doesn't know (and
shouldn't have to know) its id, so we need a different function signature.
*/
typedef
std::function<callbacks::position_entity_no_id_function>
position_entity_no_id;
}
}
}
}

#endif
