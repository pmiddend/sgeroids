#include <sgeroids/input/keyboard.hpp>
#include <sgeroids/input/log.hpp>
#include <sgeroids/model/base.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>


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
			std::tr1::bind(
				&keyboard::key,
				this,
				std::tr1::placeholders::_1))),
	add_spaceship_connection_(
		model_.add_spaceship_callback(
			std::tr1::bind(
				&keyboard::add_spaceship,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				std::tr1::placeholders::_3))),
	name_(
		_name),
	id_(),
	rotation_left_pressed_(
		false),
	rotation_right_pressed_(
		false)
{
	FCPPT_LOG_DEBUG(
		input::log(),
		fcppt::log::_ << FCPPT_TEXT("Sending the model the add_player message"));

	model_.add_player(
		_name);
}

sge::input::keyboard::device &
sgeroids::input::keyboard::device() const
{
	return device_;
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
	if(id_.get())
		model_.remove_player(
			name_);
}

void
sgeroids::input::keyboard::key(
	sge::input::keyboard::key_event const &e)
{
	if(
		!id_.get().has_value())
		return;

	switch(e.key_code())
	{
		case sge::input::keyboard::key_code::w:
			model_.change_thrust(
				*id_.get(),
				model::thrust(
					e.pressed()
					?
						50
					:
						0));
			break;
		case sge::input::keyboard::key_code::a:
			rotation_left_pressed_ =
				e.pressed();
			break;
		case sge::input::keyboard::key_code::d:
			rotation_right_pressed_ =
				e.pressed();
			break;
		default:
			break;
	}

	int const rotation_speed = 3;

	model_.rotation_direction(
		*id_.get(),
		model::rotation_direction(
			(rotation_left_pressed_ == rotation_right_pressed_
			?
				0
			:
				rotation_right_pressed_
				?
					1
				:
					-1)
			* rotation_speed * sgeroids::math::unit_magnitude()));
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
			_entity_id;
	}
}
