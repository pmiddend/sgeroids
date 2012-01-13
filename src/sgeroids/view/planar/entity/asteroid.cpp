#include <sgeroids/resource_tree/object_impl.hpp>
#include <sgeroids/resource_tree/path.hpp>
#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/view/planar/entity/asteroid.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sgeroids/view/planar/sprite/parameters.hpp>
#include <sgeroids/view/planar/sprite/system_impl.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/sprite/center.hpp>
#include <fcppt/text.hpp>


sgeroids::view::planar::entity::asteroid::asteroid(
	planar::sprite::system &_sprite_system,
	planar::texture_tree &_texture_tree,
	planar::radius &_radius)
:
	sprite_(
		planar::sprite::parameters()
			.system(
				_sprite_system)
			.size(
				planar::sprite_size_from_texture_and_radius(
					_texture_tree.get(
						sgeroids::resource_tree::path() / FCPPT_TEXT("asteroid")),
					_radius))
			.texture(
				_texture_tree.get(
						sgeroids::resource_tree::path() / FCPPT_TEXT("asteroid")))
			.order(
				4)
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
