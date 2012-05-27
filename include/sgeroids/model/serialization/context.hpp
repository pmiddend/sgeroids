#ifndef SGEROIDS_MODEL_SERIALIZATION_CONTEXT_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_CONTEXT_HPP_INCLUDED

#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <alda/serialization/context_fwd.hpp>


namespace sgeroids
{
namespace model
{
namespace serialization
{
typedef
alda::serialization::context<sgeroids::model::serialization::message::adapted_types::message>
context;
}
}
}

#endif

