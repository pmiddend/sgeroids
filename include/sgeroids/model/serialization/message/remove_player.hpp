#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_REMOVE_PLAYER_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_REMOVE_PLAYER_HPP_INCLUDED

#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/model/serialization/message/adapted_types/string.hpp>
#include <sgeroids/model/serialization/message/roles/player_name.hpp>
#include <alda/message/record.hpp>
#include <alda/message/make_id.hpp>
#include <fcppt/record/element.hpp>
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
alda::message::record
<
	alda::message::make_id
	<
		sgeroids::model::serialization::message::adapted_types::message,
		sgeroids::model::serialization::message::types::message::remove_player
	>,
	boost::mpl::vector1
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

