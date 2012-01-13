#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/resource_tree/object_impl.hpp>
#include <sgeroids/resource_tree/path.hpp>
#include <sgeroids/view/planar/position.hpp>
#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/view/planar/background/object.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sgeroids/view/planar/sprite/parameters.hpp>
#include <sgeroids/view/planar/sprite/system_impl.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/sprite/center.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/text.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/random/uniform.hpp>


sgeroids::view::planar::background::object::object(
	sgeroids::view::planar::sprite::system &_sprite_system,
	sgeroids::view::planar::texture_tree &_texture_tree,
	sgeroids::model::play_area const &_play_area,
	sgeroids::random_generator &_rng,
	star_size _star_size,
	star_count _star_count)
:
	sprite_system_(
		_sprite_system),
	texture_tree_(
		_texture_tree),
	play_area_(
		_play_area),
	rng_(
		_rng),
	star_size_(
		_star_size.get()),
	star_count_(
		_star_count.get())
{
	fcppt::random::uniform<int, sgeroids::random_generator &> random_x(
			fcppt::random::make_inclusive_range(
				0,
				play_area_.get().w()),
			rng_);

	fcppt::random::uniform<int, sgeroids::random_generator &> random_y(
			fcppt::random::make_inclusive_range(
				0,
				play_area_.get().h()),
			rng_);

	fcppt::random::uniform<float, sgeroids::random_generator &> random_angle(
			fcppt::random::make_inclusive_range(
				0.f,
				6.f),
			rng_);

	fcppt::random::uniform<int, sgeroids::random_generator &> random_radius(
		fcppt::random::make_inclusive_range(
			math::unit_magnitude() * star_size_.get(),
			math::unit_magnitude() * star_size_.get() * 4),
		rng_);

	for (int i = 0; i < star_count_.get(); ++i)
		sprites_.push_back(
			new planar::sprite::object(
				planar::sprite::parameters()
					.system(
						sprite_system_)
					.texture(
						texture_tree_.get(
								sgeroids::resource_tree::path() / FCPPT_TEXT("star")))
					.size(
						planar::sprite_size_from_texture_and_radius(
							texture_tree_.get(
								sgeroids::resource_tree::path() / FCPPT_TEXT("star")),
							planar::radius(random_radius())))
					.center(
						planar::sprite::object::vector(
							random_x(),
							random_y()))
					.order(
						0)
					.rotation(
						0)
					.any_color(
						sge::image::colors::white())));

	sprites_.push_back(
		new planar::sprite::object(
			planar::sprite::parameters()
				.system(
					sprite_system_)
				.texture(
					texture_tree_.get(
							sgeroids::resource_tree::path() / FCPPT_TEXT("planet")))
				.size(
					planar::sprite_size_from_texture_and_radius(
						texture_tree_.get(
							sgeroids::resource_tree::path() / FCPPT_TEXT("planet")),
						planar::radius(30 * random_radius())))
				.center(
					planar::sprite::object::vector(
						random_x(),
						random_y()))
				.order(
					2)
				.rotation(
					random_angle())
				.any_color(
					sge::image::colors::white())));

	sprites_.push_back(
		new planar::sprite::object(
			planar::sprite::parameters()
				.system(
					sprite_system_)
				.texture(
					texture_tree_.get(
							sgeroids::resource_tree::path() / FCPPT_TEXT("nebula")))
				.size(
					planar::sprite_size_from_texture_and_radius(
						texture_tree_.get(
							sgeroids::resource_tree::path() / FCPPT_TEXT("nebula")),
						planar::radius(math::unit_magnitude() * 1024 * 1024)))
				.center(
					planar::sprite::object::vector(
						random_x(),
						random_y()))
				.order(
					1)
				.rotation(
					random_angle())
				.any_color(
					sge::image::colors::white())));
}
