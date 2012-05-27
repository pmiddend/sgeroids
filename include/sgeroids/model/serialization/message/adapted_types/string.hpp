#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ADAPTED_TYPES_STRING_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ADAPTED_TYPES_STRING_HPP_INCLUDED

#include <sgeroids/model/serialization/message/types/string.hpp>
#include <sgeroids/model/serialization/message/adapted_types/char_type.hpp>
#include <alda/bindings/dynamic_len.hpp>

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
alda::bindings::dynamic_len
<
	sgeroids::model::serialization::message::types::string,
	sgeroids::model::serialization::message::adapted_types::char_type
>
string;
}
}
}
}
}

#endif

