#include <sgeroids/random_generator.hpp>
#include <sgeroids/math/discrete_cos.hpp>
#include <sgeroids/math/discrete_sin.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/view/planar/audio_buffer_tree.hpp>
#include <sgeroids/view/planar/player_name.hpp>
#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/callbacks/add_particle.hpp>
#include <sgeroids/view/planar/entity/spaceship.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sgeroids/view/planar/sprite/parameters.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/sprite/center.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/intrusive/ordered/collection.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iostream>
#include <fcppt/config/external_end.hpp>


sgeroids::view::planar::entity::spaceship::spaceship(
	sgeroids::view::planar::sprite::ordered_collection &_collection,
	sgeroids::view::planar::texture_tree &_texture_tree,
	sge::audio::player &_audio_player,
	sgeroids::view::planar::audio_buffer_tree &_audio_buffer_tree,
	sgeroids::view::planar::callbacks::add_particle const &_add_particle,
	sgeroids::random_generator &_rng,
	sgeroids::view::planar::radius const &_radius,
	sgeroids::view::planar::player_name const &_player_name)
:
	texture_off_(
		_texture_tree.get(
			sge::resource_tree::path() / FCPPT_TEXT("spaceship") / FCPPT_TEXT("off"))),
	texture_on_(
		_texture_tree.get(
			sge::resource_tree::path() / FCPPT_TEXT("spaceship") / FCPPT_TEXT("on"))),
	sprite_(
		planar::sprite::parameters()
			.connection(
				_collection.connection(
					3))
			.size(
				planar::sprite_size_from_texture_and_radius(
					*texture_off_,
					_radius))
			.texture(
				texture_off_)
			.rotation(
				0)
			.any_color(
				sge::image::color::predef::white())),
	audio_player_(
		_audio_player),
	thrust_sound_(
		_audio_buffer_tree.get(
			sge::resource_tree::path() / FCPPT_TEXT("thrust")
		)->create_nonpositional(
			sge::audio::sound::nonpositional_parameters())),
	add_particle_(
		_add_particle),
	rotation_rng_(
		_rng,
		int_distribution(
			int_distribution::param_type::min(
				0),
			int_distribution::param_type::max(
				360))),
	thrust_(
		false),
	player_name_(
		_player_name)
{
	thrust_sound_->play(
		sge::audio::sound::repeat::loop);
	thrust_sound_->toggle_pause();
}

void
sgeroids::view::planar::entity::spaceship::position(
	planar::position const &_position)
{
	sge::sprite::center(
		sprite_,
		_position.get());
}

void
sgeroids::view::planar::entity::spaceship::rotation(
	planar::rotation const &_rotation)
{
	sprite_.rotation(
		_rotation.get());
}

void
sgeroids::view::planar::entity::spaceship::update()
{
	if (thrust_)
		add_particle_(
			planar::position(
				sge::sprite::center(
					sprite_)
			),
			planar::particle::velocity(
					2000 * planar::vector2(
						math::discrete_cos(
							math::degrees(
								rotation_rng_())),
						math::discrete_sin(
							math::degrees(
								rotation_rng_())))),
			planar::particle::lifespan(60));
}

void
sgeroids::view::planar::entity::spaceship::change_thrust(
	model::thrust const &_thrust)
{
	std::cout << "ship changed thrust to " << _thrust.get() << "\n";
	thrust_sound_->toggle_pause();
	if (_thrust.get() > 0)
	{
		thrust_ = true;
		sprite_.texture(
			texture_on_);
	}
	else
	{
		thrust_ = false;
		sprite_.texture(
			texture_off_);
	}
}

sgeroids::view::planar::player_name const &
sgeroids::view::planar::entity::spaceship::player_name() const
{
	return
		player_name_;
}

sgeroids::view::planar::entity::spaceship::~spaceship()
{
}
