#ifndef SGEROIDS_VIEW_PLANAR_ENTITY_BASE_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_ENTITY_BASE_HPP_INCLUDED

#include <sgeroids/view/planar/position.hpp>
#include <sgeroids/view/planar/rotation.hpp>
#include <fcppt/noncopyable.hpp>


namespace sgeroids
{
namespace view
{
namespace planar
{
namespace entity
{
class base
{
FCPPT_NONCOPYABLE(
	base);
public:
	virtual void
	position(
		planar::position const &) = 0;

	virtual void
	rotation(
		planar::rotation const &) = 0;

	virtual void
	update() = 0;

	virtual ~base() = 0;
protected:
	explicit
	base();
};
}
}
}
}

#endif
