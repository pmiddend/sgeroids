#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ADAPTED_TYPES_ENTITY_ID_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ADAPTED_TYPES_ENTITY_ID_HPP_INCLUDED

#include <sgeroids/model/serialization/message/types/entity_id.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/serialization/endianness.hpp>


namespace sgeroids
{
namespace model
{
namespace serialization
{
namespace message
{
namespace adapted_types
{
typedef
alda::bindings::unsigned_
<
	sgeroids::model::serialization::message::types::entity_id,
	alda::serialization::endianness()
>
entity_id;
}
}
}
}
}

#endif

