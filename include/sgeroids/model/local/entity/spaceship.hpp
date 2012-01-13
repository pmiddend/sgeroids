#ifndef SGEROIDS_MODEL_LOCAL_ENTITY_SPACESHIP_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_ENTITY_SPACESHIP_HPP_INCLUDED

#include <sgeroids/model/play_area.hpp>
#include <sgeroids/model/player_name.hpp>
#include <sgeroids/model/rotation_direction.hpp>
#include <sgeroids/model/firing_mode.hpp>
#include <sgeroids/model/thrust.hpp>
#include <sgeroids/model/local/callbacks/position_entity_no_id.hpp>
#include <sgeroids/model/local/callbacks/rotation_entity_no_id.hpp>
#include <sgeroids/model/local/callbacks/insert_projectile.hpp>
#include <sgeroids/model/local/entity/base.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


namespace sgeroids
{
namespace model
{
namespace local
{
namespace entity
{
class spaceship
:
	public entity::base
{
FCPPT_NONCOPYABLE(
	spaceship);
public:
	explicit
	spaceship(
		model::player_name const &,
		model::position const &,
		model::rotation const &,
		model::play_area const &,
		local::callbacks::position_entity_no_id const &,
		local::callbacks::rotation_entity_no_id const &,
		local::callbacks::insert_projectile const &);

	model::player_name const &
	player_name() const;

	void
	update();

	bool
	dead() const;

	model::position const
	position() const;

	model::rotation const
	rotation() const;

	model::radius const
	radius() const;

	void
	collides_with(
		entity::base &);

	void
	rotation_direction(
		model::rotation_direction const &);

	void
	change_firing_mode(
		model::firing_mode::type);

	void
	thrust(
		model::thrust const &);

	~spaceship();
private:
	model::player_name const player_name_;
	model::rect const play_area_;
	local::callbacks::position_entity_no_id const position_entity_;
	local::callbacks::rotation_entity_no_id const rotation_entity_;
	local::callbacks::insert_projectile const insert_projectile_;
	model::vector2 position_;
	model::vector2 velocity_;
	int rotation_;
	int rotation_direction_;
	int thrust_;
	bool dead_;
	firing_mode::type firing_mode_;
	int fire_cooldown_timer_;
};
}
}
}
}

#endif
