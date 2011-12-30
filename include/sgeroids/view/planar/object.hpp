#ifndef SGEROIDS_VIEW_PLANAR_OBJECT_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_OBJECT_HPP_INCLUDED

#include <sgeroids/view/base.hpp>
#include <sgeroids/rect.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/font/device_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/box/basic_impl.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
class object
:
	public view::base
{
FCPPT_NONCOPYABLE(
	object);
public:
	explicit
	object(
		sge::renderer::device &,
		sge::font::system &);

	void
	add_spaceship(
		model::entity_id const &,
		model::player_name const &);

	void
	add_asteroid(
		model::entity_id const &,
		model::radius const &);

	void
	add_projectile(
		model::entity_id const &);

	void
	collide_projectile_asteroid(
		model::projectile_id const &,
		model::asteroid_id const &);

	void
	score_change(
		model::score const &);

	void
	destroy_asteroid(
		model::entity_id const &);

	void
	remove_entity(
		model::entity_id const &);

	void
	position_entity(
		model::entity_id const &,
		model::position const &);

	void
	rotation_entity(
		model::entity_id const &,
		model::rotation const &);

	void
	play_area(
		sgeroids::rect const &);

	void
	gameover();

	~object();
private:
	sgeroids::rect play_area_;
};
}
}
}

#endif
