#ifndef SGEROIDS_VIEW_PLANAR_ENTITY_BULLET_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_ENTITY_BULLET_HPP_INCLUDED

#include <sgeroids/view/planar/radius.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/entity/base.hpp>
#include <sgeroids/view/planar/sprite/object.hpp>
#include <sgeroids/view/planar/sprite/system.hpp>


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
	explicit
	bullet(
		planar::sprite::system &,
		planar::texture_tree &);

	void
	position(
		planar::position const &);

	void
	rotation(
		planar::rotation const &);

	void
	update();

	~bullet();
private:
	planar::sprite::object sprite_;
};
}
}
}
}

#endif
