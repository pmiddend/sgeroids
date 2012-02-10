#include <sgeroids/resource_tree/object_impl.hpp>
#include <sgeroids/resource_tree/path.hpp>
#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/view/planar/entity/asteroid.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sgeroids/view/planar/sprite/parameters.hpp>
#include <sge/image/colors.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/intrusive/ordered/collection.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/sprite/center.hpp>
#include <fcppt/text.hpp>

sgeroids::view::planar::entity::asteroid::asteroid(
	planar::sprite::ordered_collection &_collection,
	planar::texture_tree &_texture_tree,
	planar::radius const &_radius)
:
	texture_(
		_texture_tree.get(
			sgeroids::resource_tree::path() / FCPPT_TEXT("asteroid"))),
	sprite_(
		planar::sprite::parameters()
			.connection(
				_collection.connection(
					3))
			.size(
				planar::sprite_size_from_texture_and_radius(
					texture_,
					_radius))
			.texture(
				texture_)
			.rotation(
				0)
			.any_color(
				sge::image::colors::white()))
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
