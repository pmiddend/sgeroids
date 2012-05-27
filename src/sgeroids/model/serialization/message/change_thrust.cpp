#include <sgeroids/model/serialization/message/change_thrust.hpp>
#include <sgeroids/model/serialization/global_context.hpp>
#include <alda/message/instantiate_concrete.hpp>
#include <alda/serialization/instantiate_message.hpp>
#include <alda/serialization/register_message.hpp>

ALDA_MESSAGE_INSTANTIATE_CONCRETE(
	sgeroids::model::serialization::message::adapted_types::message,
	sgeroids::model::serialization::message::change_thrust);

ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(
	sgeroids::model::serialization::message::adapted_types::message,
	sgeroids::model::serialization::message::change_thrust);

ALDA_SERIALIZATION_REGISTER_MESSAGE(
	sgeroids::model::serialization::global_context(),
	sgeroids::model::serialization::message::adapted_types::message,
	sgeroids::model::serialization::message::change_thrust);
