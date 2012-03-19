#ifndef SGEROIDS_MODEL_LOCAL_ENTITY_ASTEROID_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_ENTITY_ASTEROID_HPP_INCLUDED

#include <sgeroids/model/play_area.hpp>
#include <sgeroids/model/rotation_direction.hpp>
#include <sgeroids/model/thrust.hpp>
#include <sgeroids/model/vector2.hpp>
#include <sgeroids/model/velocity.hpp>
#include <sgeroids/model/local/callbacks/position_entity_no_id.hpp>
#include <sgeroids/model/local/callbacks/rotation_entity_no_id.hpp>
#include <sgeroids/model/local/callbacks/asteroid_died.hpp>
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
class asteroid
:
	public entity::base
{
FCPPT_NONCOPYABLE(
	asteroid);
public:
	explicit
	asteroid(
		model::position const &,
		model::rotation const &,
		model::rotation_direction const &,
		model::radius const &,
		model::play_area const &,
		model::velocity const &,
		local::callbacks::position_entity_no_id const &,
		local::callbacks::rotation_entity_no_id const &,
		local::callbacks::asteroid_died const &);

	void
	update();

	bool
	dead() const;

	model::position const
	position() const;

	model::rotation const
	rotation() const;

	model::rotation_direction const
	rotation_direction() const;

	model::radius const
	radius() const;

	model::velocity const
	velocity() const;

	void
	collides_with(
		entity::base &);

	~asteroid();
private:
	model::rect const play_area_;
	int const radius_;
	local::callbacks::position_entity_no_id const position_entity_;
	local::callbacks::rotation_entity_no_id const rotation_entity_;
	local::callbacks::asteroid_died const asteroid_died_;
	sgeroids::model::vector2 position_;
	sgeroids::model::vector2 velocity_;
	int rotation_;
	int rotation_direction_;
	int health_;
	bool dead_;
};
}
}
}
}

#endif
