#include <sgeroids/input/keyboard.hpp>
#include <sgeroids/input/log.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/model/base.hpp>
#include <sgeroids/model/callbacks/add_spaceship.hpp>
#include <sgeroids/model/callbacks/remove_spaceship.hpp>
#include <sgeroids/model/serialization/message/add_player.hpp>
#include <sgeroids/model/serialization/message/change_firing_mode.hpp>
#include <sgeroids/model/serialization/message/change_thrust.hpp>
#include <sgeroids/model/serialization/message/remove_player.hpp>
#include <sgeroids/model/serialization/message/rotation_direction.hpp>
#include <sgeroids/model/serialization/message/roles/entity_id.hpp>
#include <sgeroids/model/serialization/message/roles/firing_mode.hpp>
#include <sgeroids/model/serialization/message/roles/player_name.hpp>
#include <sgeroids/model/serialization/message/roles/rotation_direction.hpp>
#include <sgeroids/model/serialization/message/roles/thrust.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sgeroids::input::keyboard::keyboard(
	sgeroids::model::base &_model,
	sge::input::keyboard::device &_device,
	sgeroids::model::player_name const &_name)
:
	model_(
		_model),
	device_(
		_device),
	key_connection_(
		_device.key_callback(
			sge::input::keyboard::key_callback{
				std::bind(
					&keyboard::key,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	add_spaceship_connection_(
		model_.get().add_spaceship_callback(
			sgeroids::model::callbacks::add_spaceship{
				std::bind(
					&keyboard::add_spaceship,
					this,
					std::placeholders::_1,
					std::placeholders::_2,
					std::placeholders::_3
				)
			}
		)
	),
	remove_spaceship_connection_(
		model_.get().remove_spaceship_callback(
			sgeroids::model::callbacks::remove_spaceship{
				std::bind(
					&keyboard::remove_spaceship,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	name_(
		_name),
	id_(
		sgeroids::input::optional_entity_id::value_type()),
	rotation_left_pressed_(
		false),
	rotation_right_pressed_(
		false)
{
	FCPPT_LOG_DEBUG(
		input::log(),
		fcppt::log::_ << FCPPT_TEXT("Sending the model the add_player message"));

	model_.get().process_message(
		sgeroids::model::serialization::message::add_player(
			sgeroids::model::serialization::message::roles::player_name{} =
				_name.get()));
}

sge::input::keyboard::device &
sgeroids::input::keyboard::device() const
{
	return device_.get();
}

sgeroids::model::player_name const &
sgeroids::input::keyboard::name() const
{
	return name_;
}

sgeroids::input::optional_entity_id const &
sgeroids::input::keyboard::id() const
{
	return id_;
}

sgeroids::input::keyboard::~keyboard()
{
	if(id_.get().has_value())
		model_.get().process_message(
			sgeroids::model::serialization::message::remove_player(
				sgeroids::model::serialization::message::roles::player_name{} =
					name_.get()));
}

void
sgeroids::input::keyboard::key(
	sge::input::keyboard::key_event const &_event
)
{
	fcppt::optional::maybe_void(
		id_.get(),
		[
			&_event,
			this
		](
			sgeroids::model::entity_id const _id
		)
		{
			this->key_impl(
				_event,
				_id
			);
		}
	);
}

void
sgeroids::input::keyboard::key_impl(
	sge::input::keyboard::key_event const &e,
	sgeroids::model::entity_id const _id
)
{
	switch(e.key().code())
	{
		case sge::input::key::code::w:
			model_.get().process_message(
				sgeroids::model::serialization::message::change_thrust(
					sgeroids::model::serialization::message::roles::entity_id{} =
						_id.get(),
					sgeroids::model::serialization::message::roles::thrust{} =
						static_cast<sgeroids::model::serialization::message::types::int_>(
							e.pressed()
							?
								100
							:
								0)));
			break;
		case sge::input::key::code::a:
			rotation_left_pressed_ =
				e.pressed();
			break;
		case sge::input::key::code::d:
			rotation_right_pressed_ =
				e.pressed();
			break;
		case sge::input::key::code::space:
			model_.get().process_message(
				sgeroids::model::serialization::message::change_firing_mode(
					sgeroids::model::serialization::message::roles::entity_id{} =
						_id.get(),
					sgeroids::model::serialization::message::roles::firing_mode{} =
						static_cast<sgeroids::model::serialization::message::types::enum_>(
							e.pressed()
							?
								model::firing_mode::enabled
							:
								model::firing_mode::disabled)));
			break;
		default:
			break;
	}

	int const rotation_speed = 3;

	model_.get().process_message(
		sgeroids::model::serialization::message::rotation_direction(
			sgeroids::model::serialization::message::roles::entity_id{} =
				_id.get(),
			sgeroids::model::serialization::message::roles::rotation_direction{} =
				static_cast<sgeroids::model::serialization::message::types::int_>(
					(rotation_left_pressed_ == rotation_right_pressed_
					?
						0
					:
						rotation_right_pressed_
						?
							1
						:
							-1)
					* rotation_speed * sgeroids::math::unit_magnitude())));
}

void
sgeroids::input::keyboard::add_spaceship(
	model::entity_id const &_entity_id,
	model::radius const &,
	model::player_name const &_name)
{

	if(name_ == _name)
	{
		FCPPT_LOG_DEBUG(
			input::log(),
			fcppt::log::_
				<< FCPPT_TEXT("We got an ID: ") << _entity_id.get());
		id_ =
			sgeroids::input::optional_entity_id(
				fcppt::optional::object<model::entity_id>(
					_entity_id));
	}
}

void
sgeroids::input::keyboard::remove_spaceship(
	model::player_name const &_name)
{
	if(name_ == _name)
	{
		FCPPT_LOG_DEBUG(
			input::log(),
			fcppt::log::_
				<< FCPPT_TEXT("In function ")
				<< __FUNCTION__);

		id_ = sgeroids::input::optional_entity_id(
			fcppt::optional::object<model::entity_id>());
	}
}
