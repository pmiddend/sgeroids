#ifndef SGEROIDS_MODEL_LOCAL_ENTITY_SPACESHIP_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_ENTITY_SPACESHIP_HPP_INCLUDED

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
		callbacks::insert_entity_function const &,
		callbacks::change_position_function const &,
		callbacks::change_rotation_function const &);

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
	callbacks::insert_entity_function const insert_entity_;
	callbacks::change_position_function const change_position_;
	callbacks::change_rotation_function const change_rotation_;
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
