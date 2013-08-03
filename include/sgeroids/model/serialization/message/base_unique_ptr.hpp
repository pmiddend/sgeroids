#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <alda/message/base_unique_ptr.hpp>


namespace sgeroids
{
namespace model
{
namespace serialization
{
namespace message
{
typedef
alda::message::base_unique_ptr
<
	sgeroids::model::serialization::message::adapted_types::message
>
base_unique_ptr;
}
}
}
}

#endif

