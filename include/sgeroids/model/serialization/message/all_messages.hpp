#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ALL_MESSAGES_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ALL_MESSAGES_HPP_INCLUDED

#include <sgeroids/model/serialization/message/add_player.hpp>
#include <sgeroids/model/serialization/message/change_firing_mode.hpp>
#include <sgeroids/model/serialization/message/change_thrust.hpp>
#include <sgeroids/model/serialization/message/rotation_direction.hpp>
#include <sgeroids/model/serialization/message/rng_seed.hpp>
#include <sgeroids/model/serialization/message/update.hpp>
#include <sgeroids/model/serialization/message/remove_player.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sgeroids
{
namespace model
{
namespace serialization
{
namespace message
{
typedef
boost::mpl::vector7
<
	sgeroids::model::serialization::message::add_player,
	sgeroids::model::serialization::message::change_firing_mode,
	sgeroids::model::serialization::message::change_thrust,
	sgeroids::model::serialization::message::rotation_direction,
	sgeroids::model::serialization::message::rng_seed,
	sgeroids::model::serialization::message::update,
	sgeroids::model::serialization::message::remove_player
>
all_messages;
}
}
}
}

#endif

