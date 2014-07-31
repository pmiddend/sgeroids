#ifndef SGEROIDS_VIEW_PLANAR_PARTICLE_OBJECT_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_PARTICLE_OBJECT_HPP_INCLUDED

#include <sgeroids/view/planar/position.hpp>
#include <sgeroids/view/planar/texture_tree_fwd.hpp>
#include <sgeroids/view/planar/particle/lifespan.hpp>
#include <sgeroids/view/planar/particle/velocity.hpp>
#include <sgeroids/view/planar/sprite/object.hpp>
#include <sgeroids/view/planar/sprite/ordered_collection.hpp>


namespace sgeroids
{
namespace view
{
namespace planar
{
namespace particle
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	object(
		planar::sprite::ordered_collection &,
		planar::texture_tree &,
		planar::position const &,
		particle::velocity const &,
		particle::lifespan const &);

	object(
		object &&
	);

	object &
	operator=(
		object &&
	);

	void
	update();

	bool
	dead();

	~object();
private:
	planar::sprite::object sprite_;
	planar::vector2 position_;
	planar::vector2 velocity_;
	particle::lifespan lifespan_;
	bool dead_;
};
}
}
}
}

#endif
