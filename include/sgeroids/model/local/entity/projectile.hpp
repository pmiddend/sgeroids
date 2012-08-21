#ifndef SGEROIDS_MODEL_LOCAL_ENTITY_PROJECTILE_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_ENTITY_PROJECTILE_HPP_INCLUDED

#include <sgeroids/model/play_area.hpp>
#include <sgeroids/model/velocity.hpp>
#include <sgeroids/model/spaceship_id.hpp>
#include <sgeroids/model/local/callbacks/position_entity_no_id.hpp>
#include <sgeroids/model/local/callbacks/rotation_entity_no_id.hpp>
#include <sgeroids/model/local/entity/base.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>

namespace sgeroids
{
namespace model
{
namespace local
{
namespace entity
{
class projectile
:
	public entity::base
{
FCPPT_NONCOPYABLE(
	projectile);
public:
	explicit
	projectile(
		sgeroids::model::position const &,
		sgeroids::model::rotation const &,
		sgeroids::model::play_area const &,
		sgeroids::model::spaceship_id const &,
		sgeroids::model::local::callbacks::position_entity_no_id const &,
		sgeroids::model::local::callbacks::rotation_entity_no_id const &);

	void
	update();

	bool
	dead() const;

	sgeroids::model::position const
	position() const;

	sgeroids::model::rotation const
	rotation() const;

	sgeroids::model::radius const
	radius() const;

	sgeroids::model::velocity const
	velocity() const;

	sgeroids::model::spaceship_id const
	owner_id() const;

	void
	collides_with(
		entity::base &);

	~projectile();
private:
	sgeroids::model::rect const play_area_;
	sgeroids::model::local::callbacks::position_entity_no_id const position_entity_;
	sgeroids::model::vector2 position_;
	int rotation_;
	int lifetime_timer_;
	bool was_hit_;
	sgeroids::model::spaceship_id owner_id_;
};
}
}
}
}

#endif
