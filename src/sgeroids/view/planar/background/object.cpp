#include <sgeroids/random_generator.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/view/planar/position.hpp>
#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/background/object.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sgeroids/view/planar/sprite/parameters.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/sprite/center.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/geometry/sort_and_update.hpp>
#include <sge/sprite/intrusive/ordered/collection_impl.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <sge/sprite/render/range_with_options.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/text.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>


sgeroids::view::planar::background::object::object(
	sge::renderer::device::core &_renderer,
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sgeroids::view::planar::texture_tree &_texture_tree,
	sgeroids::model::play_area const &_play_area,
	sgeroids::random_generator &_rng,
	star_size const _star_size,
	star_count const _star_count)
:
	sprite_buffers_(
		sge::sprite::buffers::parameters(
			_renderer,
			_vertex_declaration),
		sge::sprite::buffers::option::dynamic),
	sprite_collection_(),
	sprite_state_(
		_renderer,
		sge::sprite::state::parameters<
			sprite_state_choices
		>()),
	sprites_(),
	sprite_render_range_(),
	texture_tree_(
		_texture_tree),
	play_area_(
		_play_area),
	star_size_(
		_star_size),
	star_count_(
		_star_count)
{
	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			int
		>
	> int_distribution;

	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_real<
			float
		>
	> float_distribution;

	typedef fcppt::random::variate<
		sgeroids::random_generator,
		int_distribution
	> int_rng;

	typedef fcppt::random::variate<
		sgeroids::random_generator,
		float_distribution
	> float_rng;

	int_rng random_x(
		_rng,
		int_distribution(
			int_distribution::param_type::min(
				0),
			int_distribution::param_type::max(
				play_area_.get().w())));

	int_rng random_y(
		_rng,
		int_distribution(
			int_distribution::param_type::min(
				0),
			int_distribution::param_type::max(
				play_area_.get().h())));

	float_rng random_angle(
		_rng,
		float_distribution(
			float_distribution::param_type::min(
				0.f),
			float_distribution::param_type::sup(
				6.f)));

	int_rng random_radius(
		_rng,
		int_distribution(
			int_distribution::param_type::min(
				math::unit_magnitude() * star_size_.get()),
			int_distribution::param_type::max(
				math::unit_magnitude() * star_size_.get() * 4)));

	for (
		star_count::value_type index = 0;
		index < star_count_.get();
		++index
	)
		sprites_.push_back(
			planar::sprite::object(
				planar::sprite::parameters()
					.connection(
						sprite_collection_.connection(
							0))
					.texture(
						sgeroids::view::planar::sprite::object::texture_type{
							texture_tree_.get(
								sge::resource_tree::path() / FCPPT_TEXT("star")
							)
						}
					)
					.size(
						planar::sprite_size_from_texture_and_radius(
							*texture_tree_.get(
								sge::resource_tree::path() / FCPPT_TEXT("star")),
							planar::radius(random_radius())))
					.center(
						planar::sprite::object::vector(
							random_x(),
							random_y()))
					.rotation(
						0)
					.any_color(
						sge::image::color::predef::white())));

	sprites_.push_back(
		planar::sprite::object(
			planar::sprite::parameters()
				.connection(
					sprite_collection_.connection(
						2))
				.texture(
					sgeroids::view::planar::sprite::object::texture_type{
						texture_tree_.get(
							sge::resource_tree::path() / FCPPT_TEXT("planet")
						)
					}
				)
				.size(
					planar::sprite_size_from_texture_and_radius(
						*texture_tree_.get(
							sge::resource_tree::path() / FCPPT_TEXT("planet")),
						planar::radius(30 * random_radius())))
				.center(
					planar::sprite::object::vector(
						random_x(),
						random_y()))
				.rotation(
					random_angle())
				.any_color(
					sge::image::color::predef::white())));

	sprites_.push_back(
		planar::sprite::object(
			planar::sprite::parameters()
				.connection(
					sprite_collection_.connection(
						1))
				.texture(
					sgeroids::view::planar::sprite::object::texture_type{
						texture_tree_.get(
							sge::resource_tree::path() / FCPPT_TEXT("nebula"))
					}
				)
				.size(
					planar::sprite_size_from_texture_and_radius(
						*texture_tree_.get(
							sge::resource_tree::path() / FCPPT_TEXT("nebula")),
						planar::radius(math::unit_magnitude() * 1024 * 1024)))
				.center(
					planar::sprite::object::vector(
						random_x(),
						random_y()))
				.rotation(
					random_angle())
				.any_color(
					sge::image::color::predef::white())));


	sprite_render_range_ =
		sge::sprite::geometry::sort_and_update(
			sprite_collection_.range(),
			sge::sprite::compare::default_(),
			sprite_buffers_);
}

void
sgeroids::view::planar::background::object::render(
	sge::renderer::context::core &_render_context)
{
	sge::sprite::render::range_with_options(
		sge::sprite::render::parameters<
			sprite_state_choices
		>(
			_render_context,
			sprite_buffers_.parameters().vertex_declaration()),
		sprite_render_range_,
		sprite_state_,
		sge::sprite::state::default_options<
			sprite_state_choices
		>()
	);
}

sgeroids::view::planar::background::object::~object()
{
}
