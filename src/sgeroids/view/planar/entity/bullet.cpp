#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/resource_tree/object_impl.hpp>
#include <sgeroids/resource_tree/path.hpp>
#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/view/planar/entity/bullet.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sgeroids/view/planar/sprite/parameters.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/sprite/intrusive/ordered_collection.hpp>
#include <sge/sprite/center.hpp>
#include <sge/sprite/parameters.hpp>
#include <fcppt/text.hpp>


sgeroids::view::planar::entity::bullet::bullet(
	planar::sprite::ordered_collection &_collection,
	planar::texture_tree &_texture_tree)
:
	sprite_(
		planar::sprite::parameters()
			.connection(
				_collection.connection(
					4))
			.size(
				planar::sprite_size_from_texture_and_radius(
					_texture_tree.get(
						sgeroids::resource_tree::path() / FCPPT_TEXT("bullet")),
					planar::radius(sgeroids::math::unit_magnitude() * 1024 * 32)))
			.texture(
				_texture_tree.get(
						sgeroids::resource_tree::path() / FCPPT_TEXT("bullet")))
			.rotation(
				0)
			.any_color(
				sge::image::colors::white()))
{
}

void
sgeroids::view::planar::entity::bullet::position(
	planar::position const &_position)
{
	sge::sprite::center(
		sprite_,
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
