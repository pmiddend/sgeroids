#include <sgeroids/model/base.hpp>
#include <sgeroids/replay/dispatcher.hpp>
#include <fcppt/assert/unreachable.hpp>


sgeroids::replay::dispatcher::dispatcher(
	sgeroids::model::base &_model)
:
	model_(
		_model)
{
}

sgeroids::replay::dispatcher::result_type
sgeroids::replay::dispatcher::operator()(
	sgeroids::model::serialization::message::add_player const &_message) const
{
	model_.process_message(
		_message);
}

sgeroids::replay::dispatcher::result_type
sgeroids::replay::dispatcher::operator()(
	sgeroids::model::serialization::message::change_firing_mode const &_message) const
{
	model_.process_message(
		_message);
}

sgeroids::replay::dispatcher::result_type
sgeroids::replay::dispatcher::operator()(
	sgeroids::model::serialization::message::change_thrust const &_message) const
{
	model_.process_message(
		_message);
}

sgeroids::replay::dispatcher::result_type
sgeroids::replay::dispatcher::operator()(
	sgeroids::model::serialization::message::rotation_direction const &_message) const
{
	model_.process_message(
		_message);
}

sgeroids::replay::dispatcher::result_type
sgeroids::replay::dispatcher::operator()(
	sgeroids::model::serialization::message::rng_seed const &_message) const
{
	model_.process_message(
		_message);
}

sgeroids::replay::dispatcher::result_type
sgeroids::replay::dispatcher::operator()(
	sgeroids::model::serialization::message::update const &_message) const
{
	model_.process_message(
		_message);
}

sgeroids::replay::dispatcher::result_type
sgeroids::replay::dispatcher::operator()(
	sgeroids::model::serialization::message::remove_player const &_message) const
{
	model_.process_message(
		_message);
}

sgeroids::replay::dispatcher::~dispatcher()
{
}

void
sgeroids::replay::dispatcher::default_callback(
	sgeroids::model::serialization::message::base const &)
{
	FCPPT_ASSERT_UNREACHABLE;
}
