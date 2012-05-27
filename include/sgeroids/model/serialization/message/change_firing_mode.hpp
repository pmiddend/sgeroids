#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_CHANGE_FIRING_MODE_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_CHANGE_FIRING_MODE_HPP_INCLUDED

#include <sgeroids/model/serialization/message/adapted_types/entity_id.hpp>
#include <sgeroids/model/serialization/message/adapted_types/enum.hpp>
#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/model/serialization/message/roles/entity_id.hpp>
#include <sgeroids/model/serialization/message/roles/firing_mode.hpp>
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
		boost::mpl::vector3
		<
			alda::message::make_id
			<
				sgeroids::model::serialization::message::adapted_types::message,
				sgeroids::model::serialization::message::types::message::change_firing_mode
			>::type,
			majutsu::role
			<
				sgeroids::model::serialization::message::adapted_types::entity_id,
				sgeroids::model::serialization::message::roles::entity_id
			>,
			majutsu::role
			<
				sgeroids::model::serialization::message::adapted_types::enum_,
				sgeroids::model::serialization::message::roles::firing_mode
			>
		>
	>
>::type
change_firing_mode;
}
}
}
}

#endif

