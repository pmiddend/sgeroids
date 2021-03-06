#ifndef SGEROIDS_MODEL_LOCAL_OBJECT_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_OBJECT_HPP_INCLUDED

#include <sgeroids/random_generator.hpp>
#include <sgeroids/model/base.hpp>
#include <sgeroids/model/spaceship_id.hpp>
#include <sgeroids/model/velocity.hpp>
#include <sgeroids/model/local/error_context.hpp>
#include <sgeroids/model/local/asteroid_generator/object_fwd.hpp>
#include <sgeroids/model/local/entity/asteroid_fwd.hpp>
#include <sgeroids/model/local/entity/spaceship_fwd.hpp>
#include <sgeroids/model/local/entity/unique_base_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <map>
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
	object(
		fcppt::log::context &,
		std::ostream &
	);

	fcppt::signal::auto_connection
	add_spaceship_callback(
		sgeroids::model::callbacks::add_spaceship const &
	)
	override;

	fcppt::signal::auto_connection
	remove_spaceship_callback(
		sgeroids::model::callbacks::remove_spaceship const &
	)
	override;

	fcppt::signal::auto_connection
	add_asteroid_callback(
		sgeroids::model::callbacks::add_asteroid const &
	)
	override;

	fcppt::signal::auto_connection
	add_projectile_callback(
		sgeroids::model::callbacks::add_projectile const &
	)
	override;

	fcppt::signal::auto_connection
	collide_projectile_asteroid_callback(
		sgeroids::model::callbacks::collide_projectile_asteroid const &
	)
	override;

	fcppt::signal::auto_connection
	score_change_callback(
		sgeroids::model::callbacks::score_change const &
	)
	override;

	fcppt::signal::auto_connection
	destroy_asteroid_callback(
		sgeroids::model::callbacks::destroy_asteroid const &
	)
	override;

	fcppt::signal::auto_connection
	remove_entity_callback(
		sgeroids::model::callbacks::remove_entity const &
	)
	override;

	fcppt::signal::auto_connection
	position_entity_callback(
		sgeroids::model::callbacks::position_entity const &
	)
	override;

	fcppt::signal::auto_connection
	rotation_entity_callback(
		sgeroids::model::callbacks::rotation_entity const &
	)
	override;

	fcppt::signal::auto_connection
	gameover_callback(
		sgeroids::model::callbacks::gameover const &
	)
	override;

	fcppt::signal::auto_connection
	error_callback(
		sgeroids::model::callbacks::error const &
	)
	override;

	fcppt::signal::auto_connection
	change_thrust_callback(
		sgeroids::model::callbacks::change_thrust const &
	)
	override;

	void
	process_message(
		sgeroids::model::serialization::message::rng_seed const &
	)
	override;

	void
	process_message(
		sgeroids::model::serialization::message::update const &
	)
	override;

	/**
	\brief Try to add a player with the given name

	If the name of the player is available, this will result in at least a
	base::add_spaceship message. If the name is not available, this will
	result in the error message with code
	sgeroids::model::error_code::name_not_available.
	*/
	void
	process_message(
		sgeroids::model::serialization::message::add_player const &
	)
	override;
	/**
	\brief Remove a player
	*/
	void
	process_message(
		sgeroids::model::serialization::message::remove_player const &
	)
	override;

	/**
	\brief Set rotation (turning) of a spaceship

	Note that the rotation is not an absolute value (like "n degrees"), but
	a direction (negative is clockwise, positive is counterclockwise) with
	a magnitude. The magnitude makes sense in the context of joysticks.

	\warning
	The entity id has to refer to a spaceship, else you'll get an exception.
	*/
	void
	process_message(
		sgeroids::model::serialization::message::rotation_direction const &
	)
	override;

	void
	process_message(
		sgeroids::model::serialization::message::change_thrust const &
	)
	override;

	void
	process_message(
		sgeroids::model::serialization::message::change_firing_mode const &
	)
	override;

	model::play_area const
	play_area() const
	override;

	~object()
	override;
private:
	typedef
	fcppt::unique_ptr<
		sgeroids::model::local::entity::base
	>
	entity_unique_ptr;

	typedef
	std::map<
		model::entity_id::value_type,
		entity_unique_ptr
	>
	entity_map;

	fcppt::log::object log_;

	std::ostream &serialization_output_;

	typedef
	fcppt::unique_ptr<
		sgeroids::random_generator
	>
	random_generator_unique_ptr;

	typedef
	fcppt::optional::object<
		random_generator_unique_ptr
	>
	optional_random_generator_unique_ptr;

	optional_random_generator_unique_ptr rng_;

	model::entity_id::value_type next_id_;
	entity_map entities_;

	typedef
	fcppt::unique_ptr<
		asteroid_generator::object
	>
	asteroid_generator_unique_ptr;

	typedef
	fcppt::optional::object<
		asteroid_generator_unique_ptr
	>
	optional_asteroid_generator_unique_ptr;

	optional_asteroid_generator_unique_ptr asteroid_generator_;

	fcppt::signal::object<model::callbacks::add_spaceship_function> add_spaceship_;
	fcppt::signal::object<model::callbacks::remove_spaceship_function> remove_spaceship_;
	fcppt::signal::object<model::callbacks::add_asteroid_function> add_asteroid_;
	fcppt::signal::object<model::callbacks::add_projectile_function> add_projectile_;
	fcppt::signal::object<model::callbacks::collide_projectile_asteroid_function> collide_projectile_asteroid_;
	fcppt::signal::object<model::callbacks::score_change_function> score_change_;
	fcppt::signal::object<model::callbacks::destroy_asteroid_function> destroy_asteroid_;
	fcppt::signal::object<model::callbacks::remove_entity_function> remove_entity_;
	fcppt::signal::object<model::callbacks::position_entity_function> position_entity_;
	fcppt::signal::object<model::callbacks::rotation_entity_function> rotation_entity_;
	fcppt::signal::object<model::callbacks::gameover_function> gameover_;
	fcppt::signal::object<model::callbacks::error_function> error_;
	fcppt::signal::object<model::callbacks::change_thrust_function> change_thrust_;

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
		model::entity_id const &,
		entity::base &,
		model::entity_id const &);

	/**
	\brief Locate a spaceship with the given id or throw an error

	The functions to change spaceship attributes (object::change_thrust,
	object::start_rotation, object::end_rotation) all need to do the same
	thing: Look for an entity with the given ID, then check if it is really
	a spaceship. This function wraps just that code.
	*/
	sgeroids::model::local::entity::spaceship &
	find_spaceship_by_id_exn(
		sgeroids::model::entity_id const &,
		sgeroids::model::local::error_context const &);

	/**
	\brief Locate a spaceship with the given i

	This function is essentially the same as
	find_spaceship_by_id_exn, except it returns an optional spaceship
	instead of throwing errors when it doesn't find one.
	*/
	fcppt::optional::reference<
		sgeroids::model::local::entity::spaceship
	>
	find_spaceship_by_id(
		sgeroids::model::spaceship_id const &);

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

	/**
	\brief Called by the asteroid generator whenever a new asteroid has been generated
	*/
	void
	asteroid_generated(
		model::position const &,
		model::rotation const &,
		model::rotation_direction const &,
		model::radius const &,
		model::velocity const &);

	/**
	\brief Called by the spaceship when a new projectile is spawned
	*/
	void
	insert_projectile(
		sgeroids::model::spaceship_id const &,
		sgeroids::model::position const &,
		sgeroids::model::rotation const &);

	/**
	\brief Called by the asteroid when it dies
	*/
	void
	asteroid_died(
		model::entity_id const &,
		local::entity::asteroid &,
		model::spaceship_id const &);
};
}
}
}

#endif
