#include <sgeroids/resource_tree/object_impl.hpp>
#include <sgeroids/view/planar/entity/spaceship.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sgeoids/resource_tree/path.hpp>
#include <fcppt/config/external_end.hpp>


sgeroids::view::planar::entity::spaceship::spaceship(
	planar::sprite::system &_sprite_system,
	planar::texture_tree &_texture_tree,
	planar::radius const &_radius)
:
	sprite_(
		planar::sprite::parameters()
			.size(
				planar::sprite_size_from_texture_and_radius(
					_texture_tree.get(
						sgeroids::resource_tree::path() / FCPPT_TEXT("spaceship")),
					_radius))
			.texture(
				_texture_tree.get(
						sgeroids::resource_tree::path() / FCPPT_TEXT("spaceship")))
			.any_color(
				sge::image::colors::white()))
{
}

void
sgeroids::view::planar::entity::spaceship::position(
	planar::position const &_position)
{
	sprite_.pos(
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

sgeroids::view::planar::entity::spaceship::~spaceship()
{
}
