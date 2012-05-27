#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_BASE_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_BASE_HPP_INCLUDED

#include <alda/message/base_decl.hpp>
#include <sgeroids/model/serialization/message/adapted_types/message.hpp>

namespace sgeroids
{
namespace model
{
namespace serialization
{
namespace message
{
typedef
alda::message::base
<
	sgeroids::model::serialization::message::adapted_types::message
>
base;
}
}
}
}

#endif

