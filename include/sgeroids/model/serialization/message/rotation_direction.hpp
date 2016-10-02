#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ROTATION_DIRECTION_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ROTATION_DIRECTION_HPP_INCLUDED

#include <sgeroids/model/serialization/message/adapted_types/entity_id.hpp>
#include <sgeroids/model/serialization/message/adapted_types/int.hpp>
#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/model/serialization/message/roles/entity_id.hpp>
#include <sgeroids/model/serialization/message/roles/rotation_direction.hpp>
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
		sgeroids::model::serialization::message::types::message::rotation_direction
	>,
	boost::mpl::vector2
	<
		fcppt::record::element
		<
			sgeroids::model::serialization::message::roles::entity_id,
			sgeroids::model::serialization::message::adapted_types::entity_id
		>,
		fcppt::record::element
		<
			sgeroids::model::serialization::message::roles::rotation_direction,
			sgeroids::model::serialization::message::adapted_types::int_
		>
	>
>
rotation_direction;
}
}
}
}

#endif

