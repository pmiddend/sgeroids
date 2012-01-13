#include <sgeroids/resource_tree/object_impl.hpp>
#include <sgeroids/resource_tree/path.hpp>
#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/view/planar/entity/spaceship.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sgeroids/view/planar/sprite/parameters.hpp>
#include <sgeroids/view/planar/sprite/system_impl.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_ptr.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/sprite/center.hpp>
#include <fcppt/text.hpp>

#include <iostream>

sgeroids::view::planar::entity::spaceship::spaceship(
	planar::sprite::system &_sprite_system,
	planar::texture_tree &_texture_tree,
	sge::audio::player &_audio_player,
	planar::audio_buffer_tree &_audio_buffer_tree,
	planar::radius const &_radius)
:
	texture_off_(
		_texture_tree.get(
			sgeroids::resource_tree::path() / FCPPT_TEXT("spaceship") / FCPPT_TEXT("off"))),
	texture_on_(
		_texture_tree.get(
			sgeroids::resource_tree::path() / FCPPT_TEXT("spaceship") / FCPPT_TEXT("on"))),
	sprite_(
		planar::sprite::parameters()
			.system(
				_sprite_system)
			.size(
				planar::sprite_size_from_texture_and_radius(
					texture_off_,
					_radius))
			.texture(
				texture_off_)
			.order(
				3)
			.rotation(
				0)
			.any_color(
				sge::image::colors::white())),
	sound_thrust_(
		_audio_buffer_tree.get(
			sgeroids::resource_tree::path() / FCPPT_TEXT("thrust"))),
	audio_player_(
		_audio_player)
{
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
}

void
sgeroids::view::planar::entity::spaceship::change_thrust(
	model::thrust const &_thrust)
{
	std::cout << "ship changed thrust to " << _thrust.get() << "\n";
	if (_thrust.get() > 0)
	{
		std::cout << "playing thrust sound" << "\n";
		sound_thrust_->create_nonpositional(
			sge::audio::sound::nonpositional_parameters())->play(
				sge::audio::sound::repeat::once);
		sprite_.texture(
			texture_on_);
	}
	else
		sprite_.texture(
			texture_off_);
}

sgeroids::view::planar::entity::spaceship::~spaceship()
{
}
