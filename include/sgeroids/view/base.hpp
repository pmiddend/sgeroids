#ifndef SGEROIDS_VIEW_BASE_HPP_INCLUDED
#define SGEROIDS_VIEW_BASE_HPP_INCLUDED

#include <sgeroids/model/asteroid_id.hpp>
#include <sgeroids/model/entity_id.hpp>
#include <sgeroids/model/play_area.hpp>
#include <sgeroids/model/player_name.hpp>
#include <sgeroids/model/position.hpp>
#include <sgeroids/model/projectile_id.hpp>
#include <sgeroids/model/radius.hpp>
#include <sgeroids/model/rotation.hpp>
#include <sgeroids/model/score.hpp>
#include <sgeroids/model/spaceship_id.hpp>
#include <sgeroids/model/thrust.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sgeroids
{
namespace view
{
/**
\brief Base class for the views

This class is the "view" in the model/view/presenter idea. It gets information
about newly added, modified or destroyed entities and reacts by creating,
modifying and destroying models/sprites/line objects to display the entities.
Communication is one-way only.
*/
class base
{
FCPPT_NONCOPYABLE(
	base);
public:
	/**
	\brief Called when a spaceship (a player) is added

	The view can use the player_name to display it next to the ship (in
	case of multiple players).
	*/
	virtual void
	add_spaceship(
		model::entity_id const &,
		model::radius const &,
		model::player_name const &) = 0;

	/**
	\brief Called when an asteroid is added

	Currently, an asteroid has only the radius as its main visual property.
	Later, this message could receive a polygon describing the asteroid's
	shape.
	*/
	virtual void
	add_asteroid(
		model::entity_id const &,
		model::radius const &) = 0;

	/**
	\brief Called when a projectile is added
	*/
	virtual void
	add_projectile(
		model::entity_id const &) = 0;

	/**
	\brief Called when a projectile and an asteroid collide

	If the view wants to know the position of the projectile, it has to
	cache the position.
	*/
	virtual void
	collide_projectile_asteroid(
		model::projectile_id const &,
		model::asteroid_id const &) = 0;

	/**
	\brief Called when the score changes
	*/
	virtual void
	score_change(
		model::spaceship_id const &,
		model::score const &) = 0;

	/**
	\brief Called when an asteroid is destroyed

	The view can visualize this by adding an explosion or shaking the
	screen. However, the asteroid is not destroyed until
	view::base::remove_asteroid is called!
	*/
	virtual void
	destroy_asteroid(
		model::entity_id const &) = 0;

	/**
	\brief Called when an entity is removed

	The reason for the removal of the projectile is not given here.
	*/
	virtual void
	remove_entity(
		model::entity_id const &) = 0;

	/**
	\brief Called when the position of an entity changes
	*/
	virtual void
	position_entity(
		model::entity_id const &,
		model::position const &) = 0;

	/**
	\brief Called when the rotation of an entity changes
	*/
	virtual void
	rotation_entity(
		model::entity_id const &,
		model::rotation const &) = 0;

	/**
	\brief Called when the thrust of a spaceship changes
	*/
	virtual void
	change_thrust(
		model::entity_id const &,
		model::thrust const &) = 0;

	/**
	\brief Called when the game is over
	*/
	virtual void
	gameover() = 0;

	/**
	\brief Called to set the size of the play area.

	The view can use this information to set up the projection and world
	matrices. Note that displaying all of the play area might be too much
	because at the borders, wrapping occurs. The view should reserve some
	space for that.
	*/
	virtual void
	play_area(
		model::play_area const &) = 0;


	/**
	\brief Increase the simulation by one timestep
	*/
	virtual void
	update() = 0;

	/**
	\brief Render the stuff!
	*/
	virtual void
	render(
		sge::renderer::context::ffp &) = 0;

	virtual
	~base() = 0;
protected:
	explicit
	base();
};
}
}

#endif
