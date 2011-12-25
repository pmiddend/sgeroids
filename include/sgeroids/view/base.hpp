#ifndef SGEROIDS_VIEW_BASE_HPP_INCLUDED
#define SGEROIDS_VIEW_BASE_HPP_INCLUDED


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
		view::projectile_id const &,
		view::asteroid_id const &) = 0;

	/**
	\brief Called when the score changes
	*/
	virtual void
	score_change(
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
	\brief Called when the game is over
	*/
	virtual void
	gameover() = 0;

	virtual
	~base() = 0;
protected:
	explicit
	base();
};
}
}

#endif
