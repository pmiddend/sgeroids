#ifndef SGEROIDS_VIEW_PLANAR_ENTITY_ASTEROID_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_ENTITY_ASTEROID_HPP_INCLUDED

#include <sgeroids/model/thrust.hpp>
#include <sgeroids/view/planar/radius.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/entity/base.hpp>
#include <sgeroids/view/planar/sprite/object.hpp>
#include <sgeroids/view/planar/sprite/system.hpp>
#include <sge/texture/const_part_ptr.hpp>

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
	explicit
	asteroid(
		planar::sprite::system &,
		planar::texture_tree &,
		planar::radius const &);

	void
	position(
		planar::position const &);

	void
	rotation(
		planar::rotation const &);

	void
	update();

	~asteroid();
private:
	// We store the texture because in the sprite's constructor, we need it twice:
	// Once to calculate the sprite's size and once to actually assign it.
	sge::texture::const_part_ptr texture_;
	planar::sprite::object sprite_;
};
}
}
}
}

#endif
