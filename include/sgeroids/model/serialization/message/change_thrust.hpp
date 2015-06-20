#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_CHANGE_THRUST_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_CHANGE_THRUST_HPP_INCLUDED

#include <sgeroids/model/serialization/message/adapted_types/entity_id.hpp>
#include <sgeroids/model/serialization/message/adapted_types/int.hpp>
#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/model/serialization/message/roles/entity_id.hpp>
#include <sgeroids/model/serialization/message/roles/thrust.hpp>
#include <alda/message/make_class.hpp>
#include <alda/message/make_id.hpp>
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
	boost::mpl::vector3
	<
		alda::message::make_id
		<
			sgeroids::model::serialization::message::adapted_types::message,
			sgeroids::model::serialization::message::types::message::change_thrust
		>,
		majutsu::role
		<
			sgeroids::model::serialization::message::adapted_types::entity_id,
			sgeroids::model::serialization::message::roles::entity_id
		>,
		majutsu::role
		<
			sgeroids::model::serialization::message::adapted_types::int_,
			sgeroids::model::serialization::message::roles::thrust
		>
	>
>
change_thrust;
}
}
}
}

#endif

