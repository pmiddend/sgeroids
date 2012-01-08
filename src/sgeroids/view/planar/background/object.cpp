#include <sgeroids/resource_tree/object_impl.hpp>
#include <sgeroids/resource_tree/path.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/view/planar/background/object.hpp>
#include <sgeroids/view/planar/position.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sgeroids/view/planar/sprite/parameters.hpp>
#include <sgeroids/view/planar/sprite/system_impl.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/sprite/center.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/text.hpp>
#include <fcppt/random/uniform.hpp>
#include <fcppt/random/make_inclusive_range.hpp>

sgeroids::view::planar::background::object::object(
	sgeroids::view::planar::sprite::system &_sprite_system,
	sgeroids::view::planar::texture_tree &_texture_tree,
	sgeroids::model::play_area const &_play_area,
	sgeroids::random_generator &_rng)
:
	sprite_system_(
		_sprite_system),
	texture_tree_(
		_texture_tree),
	play_area_(
		_play_area),
	rng_(
		_rng)
{
	fcppt::random::uniform<int> random_x(
			fcppt::random::make_inclusive_range(
				0,
				play_area_.get().w()),
			rng_);

	fcppt::random::uniform<int> random_y(
			fcppt::random::make_inclusive_range(
				0,
				play_area_.get().h()),
			rng_);

	fcppt::random::uniform<int> random_radius(
			fcppt::random::make_inclusive_range(
				0,
			  math::unit_magnitude() * 15000),
			rng_);

	for (unsigned i = 0; i < 1000; ++i)
		sprites_.push_back(
			new planar::sprite::object(
				planar::sprite::parameters()
					.system(
						_sprite_system)
					.texture(
						_texture_tree.get(
								sgeroids::resource_tree::path() / FCPPT_TEXT("star")))
					.size(
						planar::sprite_size_from_texture_and_radius(
							_texture_tree.get(
								sgeroids::resource_tree::path() / FCPPT_TEXT("star")),
							planar::radius(random_radius())))
					.pos(
						planar::sprite::object::vector(
							random_x(),
							random_y()))
					.depth(
						0)
					.order(
						0)
					.rotation(
						0)
					.any_color(
						sge::image::colors::white())));
}
