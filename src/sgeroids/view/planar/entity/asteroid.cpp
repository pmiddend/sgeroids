#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/entity/asteroid.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sgeroids/view/planar/sprite/parameters.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/sprite/center.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/intrusive/ordered/collection.hpp>
#include <fcppt/text.hpp>


namespace
{

sgeroids::view::planar::sprite::parameters const
sprite_init(
	sgeroids::view::planar::sprite::ordered_collection &_collection,
	sgeroids::view::planar::texture_tree &_texture_tree,
	sgeroids::view::planar::radius const &_radius)
{
	sge::texture::const_part_shared_ptr const texture(
		_texture_tree.get(
			sge::resource_tree::path() / FCPPT_TEXT("asteroid")));

	return
		sgeroids::view::planar::sprite::parameters()
		.connection(
			_collection.connection(
				3))
		.size(
			sgeroids::view::planar::sprite_size_from_texture_and_radius(
				*texture,
				_radius))
		.texture(
			texture)
		.rotation(
			0)
		.any_color(
			sge::image::colors::white());
}

}


sgeroids::view::planar::entity::asteroid::asteroid(
	planar::sprite::ordered_collection &_collection,
	planar::texture_tree &_texture_tree,
	planar::radius const &_radius)
:
	sprite_(
		sprite_init(
			_collection,
			_texture_tree,
			_radius))
{
}

void
sgeroids::view::planar::entity::asteroid::position(
	planar::position const &_position)
{
	sge::sprite::center(
		sprite_,
		_position.get());
}

void
sgeroids::view::planar::entity::asteroid::rotation(
	planar::rotation const &_rotation)
{
	sprite_.rotation(
		_rotation.get());
}

void
sgeroids::view::planar::entity::asteroid::update()
{
}

sgeroids::view::planar::entity::asteroid::~asteroid()
{
}
