#include <sgeroids/math/discrete_cos.hpp>
#include <sgeroids/math/discrete_sin.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/math/wrap_point_in_torus.hpp>
#include <sgeroids/model/log.hpp>
#include <sgeroids/model/local/entity/asteroid.hpp>
#include <sgeroids/model/local/entity/projectile.hpp>
#include <fcppt/cast/try_dynamic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/maybe_void.hpp>


sgeroids::model::local::entity::asteroid::asteroid(
	model::position const &_position,
	model::rotation const &_rotation,
	model::rotation_direction const &_rotation_direction,
	model::radius const &_radius,
	model::play_area const &_play_area,
	model::velocity const &_velocity,
	local::callbacks::position_entity_no_id const &_position_entity,
	local::callbacks::rotation_entity_no_id const &_rotation_entity,
	local::callbacks::asteroid_died const &_asteroid_died)
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
	asteroid_died_(
		_asteroid_died),
	position_(
		_position.get()),
	velocity_(
		_velocity.get()),
	rotation_(
		_rotation.get()),
	rotation_direction_(
		_rotation_direction.get()),
	health_(
		100),
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

	if(
		velocity_
		!=
		fcppt::math::vector::null<
			vector2
		>()
	)
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

sgeroids::model::rotation_direction const
sgeroids::model::local::entity::asteroid::rotation_direction() const
{
	return
		model::rotation_direction(
			rotation_direction_);
}

sgeroids::model::radius const
sgeroids::model::local::entity::asteroid::radius() const
{
	return
		model::radius(
			radius_);
}

sgeroids::model::velocity const
sgeroids::model::local::entity::asteroid::velocity() const
{
	return
		model::velocity(
			velocity_);
}

void
sgeroids::model::local::entity::asteroid::collides_with(
	entity::base &_other)
{
	// If the entity is already dead, just return. This might happen when
	// the asteroid is big and collides with many things at once.
	if(dead_)
		return;

	// If we're not colliding with a projectile, do nothing.
	// TODO: Shall we do something here in case we're colliding with a spaceship?
	fcppt::optional::maybe_void(
		fcppt::cast::try_dynamic<
			sgeroids::model::local::entity::projectile const &
		>(
			_other
		),
		[
			this
		](
			sgeroids::model::local::entity::projectile const &_projectile
		)
		{
			// Decrease health. This could depend on the projectile later on, but
			// currently, just subtract a constant amount.
			health_ -= 50;

			// If we died, we have to tell the model, since new asteroids might
			// need to be spawned (and we're not responsible for spawning them).
			if(health_ < 0)
			{
				dead_ =
					true;

				asteroid_died_(
					*this,
					_projectile.owner_id());
			}
			// If we didn't die, our trajectory changes
			else
			{
				// TODO: No inertia here: We need to take the mass into account
				// (larger asteroids aren't as easily deflected)
				velocity_ +=
					_projectile.velocity().get()/2;
			}
		}
	);
}

sgeroids::model::local::entity::asteroid::~asteroid()
{
}
