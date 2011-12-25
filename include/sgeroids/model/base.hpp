#ifndef SGEROIDS_MODEL_BASE_HPP_INCLUDED
#define SGEROIDS_MODEL_BASE_HPP_INCLUDED

namespace sgeroids
{
namespace model
{
class base
{
FCPPT_NONCOPYABLE(
	base);
public:
	virtual void
	update() = 0;

	virtual fcppt::signal::auto_connection
	add_spaceship_callback(
		callbacks::add_spaceship const &) = 0;

	virtual fcppt::signal::auto_connection
	add_asteroid_callback(
		callbacks::add_asteroid const &) = 0;

	virtual fcppt::signal::auto_connection
	add_projectile_callback(
		callbacks::add_projectile const &) = 0;

	virtual fcppt::signal::auto_connection
	collide_projectile_asteroid_callback(
		callbacks::collide_projectile_asteroid const &) = 0;

	virtual fcppt::signal::auto_connection
	score_change_callback(
		callbacks::score_change const &) = 0;

	virtual fcppt::signal::auto_connection
	destroy_asteroid_callback(
		callbacks::destroy_asteroid const &) = 0;

	virtual fcppt::signal::auto_connection
	remove_entity_callback(
		callbacks::remove_entity const &) = 0;

	virtual fcppt::signal::auto_connection
	position_entity_callback(
		callbacks::entity_position const &) = 0;

	virtual fcppt::signal::auto_connection
	rotation_entity_callback(
		callbacks::entity_rotation const &) = 0;

	virtual fcppt::signal::auto_connection
	gameover_callback(
		callbacks::gameover const &) = 0;

	virtual void
	add_player(
		model::player_name const &);

	virtual void
	start_rotation(
		model::entity_id const &,
		model::rotation::type) = 0;

	virtual void
	end_rotation() = 0;

	virtual void
	change_thrust(
		model::entity_id const &,
		model::thrust const &) = 0;

	virtual void
	start_firing(
		model::entity_id const &) = 0;

	virtual void
	end_firing(
		model::entity_id const &) = 0;

	virtual model::play_area const
	play_area() const;

	virtual
	~base() = 0;
protected:
	explicit
	base();
};
}
}

#endif
