#include <sgeroids/math/discrete_cos.hpp>
#include <sgeroids/math/discrete_sin.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/math/wrap_point_in_torus.hpp>
#include <sgeroids/model/local/entity/asteroid.hpp>
#include <sgeroids/model/log.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/optional_dynamic_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>

sgeroids::model::local::entity::asteroid::asteroid(
	model::position const &_position,
	model::rotation const &_rotation,
	model::rotation_direction const &_rotation_direction,
	model::radius const &_radius,
	model::play_area const &_play_area,
	model::velocity const &_velocity,
	local::callbacks::position_entity_no_id const &_position_entity,
	local::callbacks::rotation_entity_no_id const &_rotation_entity)
:
	entity::base(),
	play_area_(
		_play_area.get()),
	radius_(
		_radius.get()),
	position_entity_(
		_position_entity),
	rotation_entity_(
		_rotation_entity),
	position_(
		_position.get()),
	velocity_(
		_velocity.get()),
	rotation_(
		_rotation.get()),
	rotation_direction_(
		_rotation_direction.get()),
	dead_(
		false)
{
}

void
sgeroids::model::local::entity::asteroid::update()
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

	rotation_ +=
		rotation_direction_;

	if(rotation_direction_ != 0)
		rotation_entity_(
			model::rotation(
				rotation_));
}

bool
sgeroids::model::local::entity::asteroid::dead() const
{
	return dead_;
}

sgeroids::model::position const
sgeroids::model::local::entity::asteroid::position() const
{
	return
		model::position(
			position_);
}

sgeroids::model::rotation const
sgeroids::model::local::entity::asteroid::rotation() const
{
	return
		model::rotation(
			rotation_);
}

sgeroids::model::radius const
sgeroids::model::local::entity::asteroid::radius() const
{
	return
		model::radius(
			math::unit_magnitude() * radius_);
}

void
sgeroids::model::local::entity::asteroid::collides_with(
	entity::base &/*_other*/)
{
	/*
	if(fcppt::optional_dynamic_cast<entity::asteroid const &>(_other))
		dead_ =
			true;
			*/
}

sgeroids::model::local::entity::asteroid::~asteroid()
{
}
