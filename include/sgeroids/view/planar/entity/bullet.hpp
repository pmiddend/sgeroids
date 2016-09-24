#ifndef SGEROIDS_VIEW_PLANAR_ENTITY_BULLET_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_ENTITY_BULLET_HPP_INCLUDED

#include <sgeroids/view/planar/radius.hpp>
#include <sgeroids/view/planar/texture_tree_fwd.hpp>
#include <sgeroids/view/planar/entity/base.hpp>
#include <sgeroids/view/planar/sprite/object.hpp>
#include <sgeroids/view/planar/sprite/ordered_collection.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
namespace entity
{
class bullet
:
	public entity::base
{
FCPPT_NONCOPYABLE(
	bullet);
public:
	bullet(
		planar::sprite::ordered_collection &,
		planar::texture_tree &);

	void
	position(
		planar::position const &
	)
	override;

	void
	rotation(
		planar::rotation const &
	)
	override;

	void
	update()
	override;

	~bullet()
	override;
private:
	planar::sprite::object sprite_;
};
}
}
}
}

#endif
