#ifndef SGEROIDS_MODEL_LOCAL_ENTITY_BASE_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_ENTITY_BASE_HPP_INCLUDED

#include <sgeroids/model/radius.hpp>
#include <sgeroids/model/rotation.hpp>
#include <sgeroids/model/position.hpp>
#include <fcppt/noncopyable.hpp>

namespace sgeroids
{
namespace model
{
namespace local
{
namespace entity
{
/**
\brief Base class for all model entities

This class should contain all of the properties that <em>every</em> entity needs.

It's always difficult to determine what those properties are, so in the method
documentation you will find some motivation for each of them.
*/
class base
{
FCPPT_NONCOPYABLE(
	base);
public:
	/**
	\brief "Updates" the entity

	This is, of course, highly entity-dependant. Typically, you update the
	position of the entity according to its velocity (or thrust).
	*/
	virtual void
	update() = 0;

	/**
	\brief Signals if an entity can be deleted in the next update iteration.
	*/
	virtual bool
	dead() const = 0;

	/**
	\brief Returns the entity's position (the <em>center</em>)

	This is somewhat controversial: In the future, we <em>might</em> have
	entities that do not have a position. So in theory, we could define a
	subclass of entity called <code>with_position</code> that contains a
	position. But currently, we'll keep it simple and give each entity a
	position.

	This value is used for collision detection.
	*/
	virtual model::position const
	position() const = 0;

	/**
	\brief Returns the entity's rotation

	This is somewhat controversial: In the future, we <em>might</em> have
	entities that do not have a rotation. So in theory, we could define a
	subclass of entity called <code>with_rotation</code> that contains a
	rotation. But currently, we'll keep it simple and give each entity a
	rotation.
	*/
	virtual model::rotation const
	rotation() const = 0;

	/**
	\brief Returns the entity's radius

	This value is used for collision detection.
	*/
	virtual model::radius const
	radius() const = 0;

	/**
	\brief Is called when one entity colles with another entity.
	*/
	virtual void
	collides_with(
		entity::base &) = 0;

	virtual
	~base() = 0;
protected:
	explicit
	base();
};
}
}
}
}

#endif
