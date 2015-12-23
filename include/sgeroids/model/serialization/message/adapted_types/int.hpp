#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ADAPTED_TYPES_INT_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ADAPTED_TYPES_INT_HPP_INCLUDED

#include <sgeroids/model/serialization/message/types/int.hpp>
#include <alda/bindings/fundamental.hpp>
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
alda::bindings::fundamental
<
	sgeroids::model::serialization::message::types::int_,
	alda::serialization::endianness()
>
int_;
}
}
}
}
}

#endif

