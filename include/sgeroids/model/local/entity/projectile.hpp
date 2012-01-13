#ifndef SGEROIDS_MODEL_LOCAL_ENTITY_PROJECTILE_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_ENTITY_PROJECTILE_HPP_INCLUDED

#include <sgeroids/model/play_area.hpp>
#include <sgeroids/model/local/callbacks/position_entity_no_id.hpp>
#include <sgeroids/model/local/callbacks/rotation_entity_no_id.hpp>
#include <sgeroids/model/local/entity/base.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

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
		model::position const &,
		model::rotation const &,
		model::play_area const &,
		local::callbacks::position_entity_no_id const &,
		local::callbacks::rotation_entity_no_id const &);

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

	~projectile();
private:
	model::rect const play_area_;
	local::callbacks::position_entity_no_id const position_entity_;
	model::vector2 position_;
	int rotation_;
	int lifetime_timer_;
};
}
}
}
}

#endif
