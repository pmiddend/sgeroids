#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ROTATION_DIRECTION_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ROTATION_DIRECTION_HPP_INCLUDED

#include <alda/message/make_class.hpp>
#include <alda/message/make_id.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/model/serialization/message/adapted_types/entity_id.hpp>
#include <sgeroids/model/serialization/message/adapted_types/int.hpp>
#include <sgeroids/model/serialization/message/roles/entity_id.hpp>
#include <sgeroids/model/serialization/message/roles/rotation_direction.hpp>
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
alda::message::make_class
<
	majutsu::composite
	<
		boost::mpl::vector3
		<
			alda::message::make_id
			<
				sgeroids::model::serialization::message::adapted_types::message,
				sgeroids::model::serialization::message::types::message::rotation_direction
			>::type,
			majutsu::role
			<
				sgeroids::model::serialization::message::adapted_types::entity_id,
				sgeroids::model::serialization::message::roles::entity_id
			>,
			majutsu::role
			<
				sgeroids::model::serialization::message::adapted_types::int_,
				sgeroids::model::serialization::message::roles::rotation_direction
			>
		>
	>
>::type
rotation_direction;
}
}
}
}

#endif

