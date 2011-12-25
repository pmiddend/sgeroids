#include <sgeroids/model/local/entity/spaceship.hpp>

sgeroids::model::local::entity::spaceship::spaceship(
	model::player_name const &,
	model::position const &_position,
	model::rotation const &_rotation,
	model::play_area const &_play_area,
	callbacks::insert_entity_function const &,
	callbacks::change_position_function const &,
	callbacks::change_rotation_function const &)
:
	play_area_(
		_play_area.get()),
	position_(
		_position.get()),
	velocity_(
		vector2::null()),
	rotation_(
		_rotation.get()),
	rotation_direction_(
		0),
	thrust_(
		0),
	dead_(
		false)
{
}

void
sgeroids::model::local::entity::spaceship::update()
{
	position_ +=
		velocity_;

	velocity_ +=
		thrust_ *
		sgeroids::vector2(
			math::discrete_cos(
				rotation_),
			math::discrete_sin(
				rotation_));

	rotation_ +=
		rotation_direction_;
}

bool
sgeroids::model::local::entity::spaceship::dead() const
{
	return dead_;
}

sgeroids::model::position const
sgeroids::model::local::entity::spaceship::position() const
{
	return
		model::position(
			position_);
}

sgeroids::model::rotation const
sgeroids::model::local::entity::spaceship::rotation() const
{
	return
		model::rotation(
			rotation_);
}

void
sgeroids::model::local::entity::spaceship::collides_with(
	entity::base &_other)
{
	if(fcppt::optional_dynamic_cast<entity::asteroid const &>(_other))
		dead_ =
			true;
}

void
ssgeroids::model::local::entity::spaceship::start_rotation(
	model::rotation_direction const &_rotation_direction)
{
	rotation_direction_ =
		_rotation_direction.get();
}

void
sgeroids::model::local::entity::spaceship::end_rotation()
{
	rotation_direction_ =
		0;
}

void
sgeroids::model::local::entity::spaceship::start_firing()
{
}

void
sgeroids::model::local::entity::spaceship::end_firing()
{
}

void
sgeroids::model::local::entity::spaceship::thrust(
	model::thrust const &_thrust)
{
	thrust_ =
		_thrust.get();
}

sgeroids::model::local::entity::spaceship::~spaceship()
{
}
