#ifndef SGEROIDS_VIEW_PLANAR_ENTITY_SPACESHIP_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_ENTITY_SPACESHIP_HPP_INCLUDED

#include <sgeroids/view/planar/entity/base.hpp>
#include <sgeroids/view/planar/radius.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/sprite/system.hpp>
#include <sgeroids/view/planar/sprite/object.hpp>


namespace sgeroids
{
namespace view
{
namespace planar
{
namespace entity
{
class spaceship
:
	public entity::base
{
FCPPT_NONCOPYABLE(
	spaceship);
public:
	explicit
	spaceship(
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

	~spaceship();
private:
	planar::sprite::object sprite_;
};
}
}
}
}

#endif
