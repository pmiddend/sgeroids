#ifndef SGEROIDS_VIEW_PLANAR_ENTITY_SPACESHIP_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_ENTITY_SPACESHIP_HPP_INCLUDED

#include <sgeroids/random_generator_fwd.hpp>
#include <sgeroids/model/thrust.hpp>
#include <sgeroids/view/planar/audio_buffer_tree_fwd.hpp>
#include <sgeroids/view/planar/player_name.hpp>
#include <sgeroids/view/planar/radius.hpp>
#include <sgeroids/view/planar/texture_tree_fwd.hpp>
#include <sgeroids/view/planar/callbacks/add_particle.hpp>
#include <sgeroids/view/planar/entity/base.hpp>
#include <sgeroids/view/planar/sprite/object.hpp>
#include <sgeroids/view/planar/sprite/ordered_collection.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/random/variate_decl.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_decl.hpp>


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
	spaceship(
		sgeroids::view::planar::sprite::ordered_collection &,
		sgeroids::view::planar::texture_tree &,
		sge::audio::player &,
		sgeroids::view::planar::audio_buffer_tree &,
		sgeroids::view::planar::callbacks::add_particle const &,
		sgeroids::random_generator &,
		sgeroids::view::planar::radius const &,
		sgeroids::view::planar::player_name const &);

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

	sgeroids::view::planar::player_name const &
	player_name() const;

	~spaceship();
private:
	sge::texture::const_part_shared_ptr const
		texture_off_,
		texture_on_;
	planar::sprite::object sprite_;
	sge::audio::player &audio_player_;
	sge::audio::sound::base_unique_ptr const thrust_sound_;
	planar::callbacks::add_particle const add_particle_;
	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			int
		>
	> int_distribution;
	fcppt::random::variate<sgeroids::random_generator, int_distribution> rotation_rng_;
	bool thrust_;
	sgeroids::view::planar::player_name const player_name_;
};
}
}
}
}

#endif
