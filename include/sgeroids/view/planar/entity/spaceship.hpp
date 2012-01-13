#ifndef SGEROIDS_VIEW_PLANAR_ENTITY_SPACESHIP_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_ENTITY_SPACESHIP_HPP_INCLUDED

#include <sge/audio/player_fwd.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sgeroids/model/thrust.hpp>
#include <sgeroids/view/planar/audio_buffer_tree.hpp>
#include <sgeroids/view/planar/radius.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/entity/base.hpp>
#include <sgeroids/view/planar/sprite/object.hpp>
#include <sgeroids/view/planar/sprite/system.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sge/audio/sound/base_ptr.hpp>


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
		sge::audio::player &,
		planar::audio_buffer_tree &,
		planar::radius const &);

	void
	position(
		planar::position const &);

	void
	rotation(
		planar::rotation const &);

	void
	update();

	void
	change_thrust(
		model::thrust const &);

	~spaceship();
private:
	sge::texture::const_part_ptr
		texture_off_,
		texture_on_;
	planar::sprite::object sprite_;
	sge::audio::player &audio_player_;
	sge::audio::sound::base_ptr thrust_sound_;
};
}
}
}
}

#endif
