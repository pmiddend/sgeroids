#include <sgeroids/math/discrete_cos.hpp>
#include <sgeroids/math/discrete_sin.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/math/wrap_point_in_torus.hpp>
#include <sgeroids/model/log.hpp>
#include <sgeroids/model/local/entity/asteroid.hpp>
#include <sgeroids/model/local/entity/projectile.hpp>
#include <fcppt/optional_dynamic_cast.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sgeroids::model::local::entity::projectile::projectile(
	model::position const &_position,
	model::rotation const &_rotation,
	model::play_area const &_play_area,
	local::callbacks::position_entity_no_id const &_position_entity,
	local::callbacks::rotation_entity_no_id const &)
:
	entity::base(),
	play_area_(
		_play_area.get()),
	position_entity_(
		_position_entity),
	position_(
		_position.get()),
	rotation_(
		_rotation.get()),
	lifetime_timer_(3*60),
	was_hit_(
		false)
{
}

void
sgeroids::model::local::entity::projectile::update()
{
	position_ +=
		14900 *
			model::vector2(
				math::discrete_cos(
					rotation_ / math::unit_magnitude()),
				math::discrete_sin(
					rotation_ / math::unit_magnitude()));

	position_ =
		sgeroids::math::wrap_point_in_torus(
			position_,
			play_area_);

	position_entity_(
		model::position(
			position_));

	lifetime_timer_ =
		lifetime_timer_ > 0
		?
			lifetime_timer_-1
		:
			lifetime_timer_;
}

bool
sgeroids::model::local::entity::projectile::dead() const
{
	return lifetime_timer_ <= 0 || was_hit_;
}

sgeroids::model::position const
sgeroids::model::local::entity::projectile::position() const
{
	return
		model::position(
			position_);
}

sgeroids::model::rotation const
sgeroids::model::local::entity::projectile::rotation() const
{
	return
		model::rotation(
			rotation_);
}

sgeroids::model::radius const
sgeroids::model::local::entity::projectile::radius() const
{
	return
		model::radius(
			math::unit_magnitude() * 5000);
}

void
sgeroids::model::local::entity::projectile::collides_with(
	entity::base &_other)
{
	if(fcppt::optional_dynamic_cast<entity::asteroid const &>(_other))
		was_hit_ =
			true;
}

sgeroids::model::local::entity::projectile::~projectile()
{
}
