#ifndef SGEROIDS_REPLAY_CALL_OBJECT_HPP_INCLUDED
#define SGEROIDS_REPLAY_CALL_OBJECT_HPP_INCLUDED

#include <sgeroids/model/serialization/message/all_messages.hpp>
#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/replay/dispatcher_fwd.hpp>
#include <alda/call/object_fwd.hpp>


namespace sgeroids
{
namespace replay
{
typedef
alda::call::object
<
	sgeroids::model::serialization::message::adapted_types::message,
	sgeroids::model::serialization::message::all_messages,
	sgeroids::replay::dispatcher
>
call_object;
}
}

#endif

