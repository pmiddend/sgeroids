#ifndef SGEROIDS_MODEL_LOCAL_CALLBACKS_ASTEROID_DIED_FUNCTION_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_CALLBACKS_ASTEROID_DIED_FUNCTION_HPP_INCLUDED

#include <sgeroids/model/spaceship_id.hpp>
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
	sgeroids::model::local::entity::asteroid &,
	sgeroids::model::spaceship_id const &);
}
}
}
}

#endif
