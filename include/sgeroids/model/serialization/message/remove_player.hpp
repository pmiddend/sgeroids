#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_REMOVE_PLAYER_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_REMOVE_PLAYER_HPP_INCLUDED

#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/model/serialization/message/adapted_types/string.hpp>
#include <sgeroids/model/serialization/message/roles/player_name.hpp>
#include <alda/bindings/record_variadic.hpp>
#include <alda/message/object.hpp>
#include <alda/message/make_id.hpp>
#include <fcppt/record/element.hpp>


namespace sgeroids
{
namespace model
{
namespace serialization
{
namespace message
{
typedef
alda::message::object
<
	alda::message::make_id
	<
		sgeroids::model::serialization::message::adapted_types::message,
		sgeroids::model::serialization::message::types::message::remove_player
	>,
	alda::bindings::record_variadic
	<
		fcppt::record::element
		<
			sgeroids::model::serialization::message::roles::player_name,
			sgeroids::model::serialization::message::adapted_types::string
		>
	>
>
remove_player;
}
}
}
}

#endif

