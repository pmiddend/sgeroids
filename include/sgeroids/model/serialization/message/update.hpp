#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_UPDATE_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_UPDATE_HPP_INCLUDED

#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/model/serialization/message/types/message.hpp>
#include <alda/bindings/unit.hpp>
#include <alda/message/object.hpp>
#include <alda/message/make_id.hpp>


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
		sgeroids::model::serialization::message::types::message::update
	>,
	alda::bindings::unit
>
update;
}
}
}
}

#endif

