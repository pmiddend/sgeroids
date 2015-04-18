#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/entity/bullet.hpp>
#include <sgeroids/view/planar/sprite/color_format.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
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


sgeroids::view::planar::entity::bullet::bullet(
	planar::sprite::ordered_collection &_collection,
	planar::texture_tree &_texture_tree)
:
	sprite_(
		sge::sprite::roles::connection{} =
			_collection.connection(
				4
			),
		sge::sprite::roles::size{} =
			planar::sprite_size_from_texture_and_radius(
				*_texture_tree.get(
					sge::resource_tree::path() / FCPPT_TEXT("bullet")),
				planar::radius(sgeroids::math::unit_magnitude() * 1024 * 32)
			),
		sge::sprite::roles::texture0{} =
			sgeroids::view::planar::sprite::object::texture_type{
				_texture_tree.get(
					sge::resource_tree::path() / FCPPT_TEXT("bullet")
				)
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
	)
{
}

void
sgeroids::view::planar::entity::bullet::position(
	planar::position const &_position)
{
	sprite_.center(
		_position.get());
}

void
sgeroids::view::planar::entity::bullet::rotation(
	planar::rotation const &_rotation)
{
	sprite_.rotation(
		_rotation.get());
}

void
sgeroids::view::planar::entity::bullet::update()
{
}

sgeroids::view::planar::entity::bullet::~bullet()
{
}
