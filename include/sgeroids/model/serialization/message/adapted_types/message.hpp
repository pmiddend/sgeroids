#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ADAPTED_TYPES_MESSAGE_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ADAPTED_TYPES_MESSAGE_HPP_INCLUDED

#include <sgeroids/model/serialization/message/types/message.hpp>
#include <alda/type_enum.hpp>


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
alda::type_enum
<
	sgeroids::model::serialization::message::types::message,
	sgeroids::model::serialization::message::types::message::size
>
message;
}
}
}
}
}

#endif

