#include <sgeroids/math/discrete_cos.hpp>
#include <sgeroids/math/discrete_sin.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/math/wrap_point_in_torus.hpp>
#include <sgeroids/model/log.hpp>
#include <sgeroids/model/local/entity/spaceship.hpp>
#include <fcppt/optional_dynamic_cast.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <iostream>
#include <fcppt/config/external_end.hpp>


sgeroids::model::local::entity::spaceship::spaceship(
	sgeroids::model::player_name const &_player_name,
	sgeroids::model::position const &_position,
	sgeroids::model::rotation const &_rotation,
	sgeroids::model::play_area const &_play_area,
	sgeroids::model::local::callbacks::position_entity_no_id const &_position_entity,
	sgeroids::model::local::callbacks::rotation_entity_no_id const &_rotation_entity,
	sgeroids::model::local::callbacks::insert_projectile const &_insert_projectile)
:
	entity::base(),
	player_name_(
		_player_name),
	play_area_(
		_play_area.get()),
	position_entity_(
		_position_entity),
	rotation_entity_(
		_rotation_entity),
	insert_projectile_(
		_insert_projectile),
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
		false),
	firing_mode_(
		firing_mode::disabled),
	fire_cooldown_timer_(),
	score_(
		model::score(
			0))
{
}

sgeroids::model::player_name const &
sgeroids::model::local::entity::spaceship::player_name() const
{
	return player_name_;
}

void
sgeroids::model::local::entity::spaceship::update()
{
	position_ +=
		velocity_;

	position_ =
		sgeroids::math::wrap_point_in_torus(
			position_,
			play_area_);

	if(velocity_ != vector2::null())
		position_entity_(
			model::position(
				position_));

	velocity_ +=
		thrust_ *
		model::vector2(
			math::discrete_cos(
				math::degrees(
					rotation_ / sgeroids::math::unit_magnitude())),
			math::discrete_sin(
				math::degrees(
					rotation_ / sgeroids::math::unit_magnitude())));

	velocity_ =
		model::vector2(
			std::min(
				velocity_.x(),
				14900000),
			std::min(
				velocity_.y(),
				14900000));

	rotation_ +=
		rotation_direction_;

	if(rotation_direction_ != 0)
		rotation_entity_(
			model::rotation(
				rotation_));

	if(firing_mode_ == model::firing_mode::enabled)
	{
		if(--fire_cooldown_timer_ == 0)
		{
			fire_cooldown_timer_ = 30;
			insert_projectile_(
				model::position(
					position_),
				model::rotation(
					rotation_));
		}
	}
}

bool
sgeroids::model::local::entity::spaceship::dead() const
{
	return dead_;
}

void
sgeroids::model::local::entity::spaceship::kill()
{
	dead_ = true;
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

sgeroids::model::radius const
sgeroids::model::local::entity::spaceship::radius() const
{
	return
		model::radius(
			math::unit_magnitude() * 60000);
}

sgeroids::model::score const
sgeroids::model::local::entity::spaceship::score() const
{
	return
		score_;
}

void
sgeroids::model::local::entity::spaceship::increase_score(
	sgeroids::model::score const &_inc)
{
	score_ +=
		_inc;
}

void
sgeroids::model::local::entity::spaceship::collides_with(
	entity::base &/*_other*/)
{
	/*
	if(fcppt::optional_dynamic_cast<entity::asteroid const &>(_other))
		this->kill();
			*/
}

void
sgeroids::model::local::entity::spaceship::rotation_direction(
	model::rotation_direction const &_rotation_direction)
{
	rotation_direction_ =
		_rotation_direction.get();
}

void
sgeroids::model::local::entity::spaceship::change_firing_mode(
	model::firing_mode const _firing_mode)
{
	if(firing_mode_ == _firing_mode)
		return;

	firing_mode_ =
		_firing_mode;

	if(firing_mode_ == model::firing_mode::enabled)
		fire_cooldown_timer_ = 1;
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
