#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_TYPES_MESSAGE_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_TYPES_MESSAGE_HPP_INCLUDED

#include <sgeroids/model/serialization/message/types/message_fwd.hpp>


namespace sgeroids
{
namespace model
{
namespace serialization
{
namespace message
{
namespace types
{

enum class message
{
	update,
	rng_seed,
	add_player,
	remove_player,
	rotation_direction,
	change_thrust,
	change_firing_mode,
	fcppt_maximum = change_firing_mode
};

}
}
}
}
}

#endif
