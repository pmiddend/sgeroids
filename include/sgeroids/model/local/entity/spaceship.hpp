#ifndef SGEROIDS_MODEL_LOCAL_ENTITY_SPACESHIP_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_ENTITY_SPACESHIP_HPP_INCLUDED

#include <sgeroids/model/local/entity/base.hpp>
#include <sgeroids/model/callbacks/position_entity.hpp>
#include <sgeroids/model/callbacks/rotation_entity.hpp>
#include <sgeroids/model/rotation_direction.hpp>
#include <sgeroids/model/thrust.hpp>
#include <sgeroids/model/player_name.hpp>
#include <sgeroids/model/play_area.hpp>

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
		callbacks::position_entity const &,
		callbacks::rotation_entity const &);

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
	start_rotation(
		model::rotation_direction const &);

	void
	end_rotation();

	void
	start_firing();

	void
	end_firing();

	void
	thrust(
		model::thrust const &);

	~spaceship();
private:
	sgeroids::rect const play_area_;
	callbacks::position_entity const position_entity_;
	callbacks::rotation_entity const rotation_entity_;
	sgeroids::vector2 position_;
	sgeroids::vector2 velocity_;
	int rotation_;
	int rotation_direction_;
	int thrust_;
	bool dead_;
};
}
}
}
}

#endif
