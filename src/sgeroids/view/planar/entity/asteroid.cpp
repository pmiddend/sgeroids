#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/entity/asteroid.hpp>
#include <sgeroids/view/planar/sprite/color_format.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sgeroids/view/planar/sprite/object.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/sprite/intrusive/ordered/collection.hpp>
#include <sge/sprite/roles/center.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <fcppt/text.hpp>


namespace
{

sgeroids::view::planar::sprite::object
sprite_init(
	sgeroids::view::planar::sprite::ordered_collection &_collection,
	sgeroids::view::planar::texture_tree &_texture_tree,
	sgeroids::view::planar::radius const &_radius)
{
	sge::texture::const_part_shared_ptr const texture(
		_texture_tree.get(
			sge::resource_tree::path() / FCPPT_TEXT("asteroid")));

	return
		sgeroids::view::planar::sprite::object(
			sge::sprite::roles::connection{} =
				_collection.connection(
					3
				),
			sge::sprite::roles::size{} =
				sgeroids::view::planar::sprite_size_from_texture_and_radius(
					*texture,
					_radius
				),
			sge::sprite::roles::texture0{} =
				sgeroids::view::planar::sprite::object::texture_type{
					texture
				},
			sge::sprite::roles::rotation{} =
				0.f,
			sge::sprite::roles::color{} =
				sge::image::color::any::convert<
					sgeroids::view::planar::sprite::color_format
				>(
					sge::image::color::predef::white()
				),
			sge::sprite::roles::center{} =
				sgeroids::view::planar::sprite::object::vector::null()
		);
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
	sprite_.center(
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
