#include <sgeroids/model/serialization/global_context.hpp>
#include <sgeroids/model/serialization/message/base_unique_ptr.hpp>
#include <sgeroids/replay/object.hpp>
#include <alda/serialization/deserialize.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>


sgeroids::replay::object::object(
	sgeroids::model::base &_model,
	std::istream &_input_stream)
:
	input_stream_(
		_input_stream),
	call_object_(),
	dispatcher_(
		_model)
{
}

void
sgeroids::replay::object::update()
{
	while(
		!this->deserialize_single_message().get())
		;
}

bool
sgeroids::replay::object::done() const
{
	return
		input_stream_.eof();
}

sgeroids::replay::object::~object()
{
}

sgeroids::replay::object::was_update_message const
sgeroids::replay::object::deserialize_single_message()
{
	sgeroids::model::serialization::message::base_unique_ptr message(
		alda::serialization::deserialize(
			sgeroids::model::serialization::global_context(),
			input_stream_));

	sgeroids::replay::object::was_update_message const was_update(
		message->type() == sgeroids::model::serialization::message::types::message::update);

	if(
		was_update.get())
		return
			was_update;

	call_object_(
		*message,
		dispatcher_,
		sgeroids::replay::call_object::default_function(
			std::tr1::bind(
				&sgeroids::replay::dispatcher::default_callback,
				&dispatcher_,
				std::tr1::placeholders::_1)));
	return
		was_update;
}
