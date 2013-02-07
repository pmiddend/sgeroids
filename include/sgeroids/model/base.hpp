#ifndef SGEROIDS_MODEL_BASE_HPP_INCLUDED
#define SGEROIDS_MODEL_BASE_HPP_INCLUDED

#include <sgeroids/random_generator.hpp>
#include <sgeroids/model/entity_id.hpp>
#include <sgeroids/model/firing_mode.hpp>
#include <sgeroids/model/play_area.hpp>
#include <sgeroids/model/player_name.hpp>
#include <sgeroids/model/rotation_direction.hpp>
#include <sgeroids/model/thrust.hpp>
#include <sgeroids/model/callbacks/add_asteroid.hpp>
#include <sgeroids/model/callbacks/add_projectile.hpp>
#include <sgeroids/model/callbacks/add_spaceship.hpp>
#include <sgeroids/model/callbacks/remove_spaceship.hpp>
#include <sgeroids/model/callbacks/change_thrust.hpp>
#include <sgeroids/model/callbacks/collide_projectile_asteroid.hpp>
#include <sgeroids/model/callbacks/destroy_asteroid.hpp>
#include <sgeroids/model/callbacks/error.hpp>
#include <sgeroids/model/callbacks/gameover.hpp>
#include <sgeroids/model/callbacks/position_entity.hpp>
#include <sgeroids/model/callbacks/remove_entity.hpp>
#include <sgeroids/model/callbacks/rotation_entity.hpp>
#include <sgeroids/model/callbacks/score_change.hpp>
#include <sgeroids/model/serialization/message/add_player.hpp>
#include <sgeroids/model/serialization/message/change_firing_mode.hpp>
#include <sgeroids/model/serialization/message/change_thrust.hpp>
#include <sgeroids/model/serialization/message/remove_player.hpp>
#include <sgeroids/model/serialization/message/rng_seed.hpp>
#include <sgeroids/model/serialization/message/rotation_direction.hpp>
#include <sgeroids/model/serialization/message/update.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sgeroids
{
namespace model
{
/**
\brief The base class for all models

This class represents the model in the model-view-presenter scheme. You can
communicate in both ways with the model: You can either register for a signal
(like "score changed") or you can send it a message by calling a function.
*/
class base
{
FCPPT_NONCOPYABLE(
	base);
public:
	virtual fcppt::signal::auto_connection
	add_spaceship_callback(
		callbacks::add_spaceship const &) = 0;
	
	virtual fcppt::signal::auto_connection
	remove_spaceship_callback(
		callbacks::remove_spaceship const &) = 0;

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
		callbacks::position_entity const &) = 0;

	virtual fcppt::signal::auto_connection
	rotation_entity_callback(
		callbacks::rotation_entity const &) = 0;

	virtual fcppt::signal::auto_connection
	gameover_callback(
		callbacks::gameover const &) = 0;

	virtual fcppt::signal::auto_connection
	error_callback(
		callbacks::error const &) = 0;

	virtual fcppt::signal::auto_connection
	change_thrust_callback(
		callbacks::change_thrust const &) = 0;

	virtual void
	process_message(
		sgeroids::model::serialization::message::rng_seed const &) = 0;

	virtual void
	process_message(
		sgeroids::model::serialization::message::update const &) = 0;

	/**
	\brief Try to add the player with the given name.

	This operation might not result in a new player being added, but in an
	error message. That's because a name must be unique.
	*/
	virtual void
	process_message(
		sgeroids::model::serialization::message::add_player const &) = 0;

	/**
	\brief Remove a player with the given name
	*/
	virtual void
	process_message(
		sgeroids::model::serialization::message::remove_player const &) = 0;

	/**
	\brief Set the rotation direction (and speed) of the entity
	*/
	virtual void
	process_message(
		sgeroids::model::serialization::message::rotation_direction const &) = 0;

	virtual void
	process_message(
		sgeroids::model::serialization::message::change_thrust const &) = 0;

	virtual void
	process_message(
		sgeroids::model::serialization::message::change_firing_mode const &) = 0;

	virtual model::play_area const
	play_area() const = 0;

	virtual
	~base() = 0;
protected:
	explicit
	base();
};
}
}

#endif
