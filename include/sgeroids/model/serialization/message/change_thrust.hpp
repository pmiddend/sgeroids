#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_CHANGE_THRUST_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_CHANGE_THRUST_HPP_INCLUDED

#include <sgeroids/model/serialization/message/adapted_types/entity_id.hpp>
#include <sgeroids/model/serialization/message/adapted_types/int.hpp>
#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/model/serialization/message/roles/entity_id.hpp>
#include <sgeroids/model/serialization/message/roles/thrust.hpp>
#include <alda/bindings/record_variadic.hpp>
#include <alda/message/make_id.hpp>
#include <alda/message/object.hpp>
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
		sgeroids::model::serialization::message::types::message::change_thrust
	>,
	alda::bindings::record_variadic
	<
		fcppt::record::element
		<
			sgeroids::model::serialization::message::roles::entity_id,
			sgeroids::model::serialization::message::adapted_types::entity_id
		>,
		fcppt::record::element
		<
			sgeroids::model::serialization::message::roles::thrust,
			sgeroids::model::serialization::message::adapted_types::int_
		>
	>
>
change_thrust;
}
}
}
}

#endif

