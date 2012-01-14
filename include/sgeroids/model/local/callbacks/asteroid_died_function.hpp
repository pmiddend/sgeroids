#ifndef SGEROIDS_MODEL_LOCAL_CALLBACKS_ASTEROID_DIED_FUNCTION_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_CALLBACKS_ASTEROID_DIED_FUNCTION_HPP_INCLUDED

#include <sgeroids/model/entity_id.hpp>
#include <sgeroids/model/local/entity/asteroid_fwd.hpp>

namespace sgeroids
{
namespace model
{
namespace local
{
namespace callbacks
{
typedef
void
asteroid_died_function(
	entity::asteroid &);
}
}
}
}

#endif
