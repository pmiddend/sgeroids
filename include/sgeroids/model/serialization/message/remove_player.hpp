#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_REMOVE_PLAYER_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_REMOVE_PLAYER_HPP_INCLUDED

#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/model/serialization/message/adapted_types/string.hpp>
#include <sgeroids/model/serialization/message/roles/player_name.hpp>
#include <alda/message/make_class.hpp>
#include <alda/message/make_id.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace model
{
namespace serialization
{
namespace message
{
typedef
alda::message::make_class
<
	majutsu::composite
	<
		boost::mpl::vector2
		<
			alda::message::make_id
			<
				sgeroids::model::serialization::message::adapted_types::message,
				sgeroids::model::serialization::message::types::message::remove_player
			>,
			majutsu::role
			<
				sgeroids::model::serialization::message::adapted_types::string,
				sgeroids::model::serialization::message::roles::player_name
			>
		>
	>
>
remove_player;
}
}
}
}

#endif

