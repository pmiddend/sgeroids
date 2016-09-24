#ifndef SGEROIDS_VIEW_PLANAR_ENTITY_ASTEROID_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_ENTITY_ASTEROID_HPP_INCLUDED

#include <sgeroids/model/thrust.hpp>
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
class asteroid
:
	public entity::base
{
FCPPT_NONCOPYABLE(
	asteroid);
public:
	asteroid(
		planar::sprite::ordered_collection &,
		planar::texture_tree &,
		planar::radius const &);

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

	~asteroid()
	override;
private:
	planar::sprite::object sprite_;
};
}
}
}
}

#endif
