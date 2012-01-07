#ifndef SGEROIDS_MODEL_LOCAL_OBJECT_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_OBJECT_HPP_INCLUDED

#include <sgeroids/model/base.hpp>
#include <sgeroids/model/local/error_context.hpp>
#include <sgeroids/model/local/entity/spaceship_fwd.hpp>
#include <sgeroids/model/local/entity/unique_base_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace model
{
namespace local
{
/**
\brief Represents a "local" model in the sense that no networking occurs.
*/
class object
:
	public model::base
{
FCPPT_NONCOPYABLE(
	object);
public:
	explicit
	object();

	void
	update();

	fcppt::signal::auto_connection
	add_spaceship_callback(
		model::callbacks::add_spaceship const &);

	fcppt::signal::auto_connection
	add_asteroid_callback(
		model::callbacks::add_asteroid const &);

	fcppt::signal::auto_connection
	add_projectile_callback(
		model::callbacks::add_projectile const &);

	fcppt::signal::auto_connection
	collide_projectile_asteroid_callback(
		model::callbacks::collide_projectile_asteroid const &);

	fcppt::signal::auto_connection
	score_change_callback(
		model::callbacks::score_change const &);

	fcppt::signal::auto_connection
	destroy_asteroid_callback(
		model::callbacks::destroy_asteroid const &);

	fcppt::signal::auto_connection
	remove_entity_callback(
		model::callbacks::remove_entity const &);

	fcppt::signal::auto_connection
	position_entity_callback(
		model::callbacks::position_entity const &);

	fcppt::signal::auto_connection
	rotation_entity_callback(
		model::callbacks::rotation_entity const &);

	fcppt::signal::auto_connection
	gameover_callback(
		model::callbacks::gameover const &);

	fcppt::signal::auto_connection
	error_callback(
		model::callbacks::error const &);

	/**
	\brief Try to add a player with the given name

	If the name of the player is available, this will result in at least a
	base::add_spaceship message. If the name is not available, this will
	result in the error message with code
	sgeroids::model::error_code::name_not_available.
	*/
	void
	add_player(
		model::player_name const &);
	/**
	\brief Remove a player
	*/
	void
	remove_player(
		model::player_name const &);

	/**
	\brief Start rotation (turning) of a spaceship

	Note that the rotation is not an absolute value (like "n degrees"), but
	a direction (negative is clockwise, positive is counterclockwise) with
	a magnitude. The magnitude makes sense in the context of joysticks.

	\warning
	The entity id has to refer to a spaceship, else you'll get an exception.
	*/
	void
	start_rotation(
		model::entity_id const &,
		model::rotation_direction const &);

	/**
	\brief End rotation (turning) of a spaceship
	*/
	void
	end_rotation(
		model::entity_id const &);

	void
	change_thrust(
		model::entity_id const &,
		model::thrust const &);

	void
	start_firing(
		model::entity_id const &);

	void
	end_firing(
		model::entity_id const &);

	model::play_area const
	play_area() const;

	~object();
private:
	typedef
	boost::ptr_map<model::entity_id::value_type,entity::base>
	entity_map;

	model::entity_id::value_type next_id_;
	entity_map entities_;
	fcppt::signal::object<callbacks::add_spaceship_function> add_spaceship_;
	fcppt::signal::object<callbacks::add_asteroid_function> add_asteroid_;
	fcppt::signal::object<callbacks::add_projectile_function> add_projectile_;
	fcppt::signal::object<callbacks::collide_projectile_asteroid_function> collide_projectile_asteroid_;
	fcppt::signal::object<callbacks::score_change_function> score_change_;
	fcppt::signal::object<callbacks::destroy_asteroid_function> destroy_asteroid_;
	fcppt::signal::object<callbacks::remove_entity_function> remove_entity_;
	fcppt::signal::object<callbacks::position_entity_function> position_entity_;
	fcppt::signal::object<callbacks::rotation_entity_function> rotation_entity_;
	fcppt::signal::object<callbacks::gameover_function> gameover_;
	fcppt::signal::object<callbacks::error_function> error_;

	/**
	\brief Updates all entities, deletes the dead ones
	*/
	void
	entity_updates();

	/**
	\brief Determines which pairs of entities are able to collide and calls the narrow phase
	*/
	void
	collision_detection_broadphase();

	/**
	\brief Determines if two entities are really colliding and calls entity::base::collides_with.
	*/
	void
	collision_detection_narrow_phase(
		entity::base &,
		entity::base &);

	/**
	\brief Locate a spaceship with the given id or throw an error

	The functions to change spaceship attributes (object::change_thrust,
	object::start_rotation, object::end_rotation) all need to do the same
	thing: Look for an entity with the given ID, then check if it is really
	a spaceship. This function wraps just that code.
	*/
	entity::spaceship &
	search_spaceship_with_id(
		model::entity_id const &,
		local::error_context const &);

	void
	change_entity_position(
		model::entity_id const &,
		model::position const &);

	void
	change_entity_rotation(
		model::entity_id const &,
		model::rotation const &);

	/**
	\brief Given as a callback to all entities that need to spawn other entities

	In this function, the entity is given an ID and inserted into the
	entity map.
	*/
	void
	insert_entity(
		entity::unique_base_ptr);
};
}
}
}

#endif
