#include <sgeroids/exception.hpp>
#include <sgeroids/log_location.hpp>
#include <sgeroids/log_parameters.hpp>
#include <sgeroids/media_path.hpp>
#include <sgeroids/random_generator_seed.hpp>
#include <sgeroids/model/asteroid_id.hpp>
#include <sgeroids/model/entity_id.hpp>
#include <sgeroids/model/projectile_id.hpp>
#include <sgeroids/model/spaceship_id.hpp>
#include <sgeroids/view/planar/object.hpp>
#include <sgeroids/view/planar/player_name.hpp>
#include <sgeroids/view/planar/radius_to_screen_space.hpp>
#include <sgeroids/view/planar/rotation_to_screen_space.hpp>
#include <sgeroids/view/planar/entity/asteroid.hpp>
#include <sgeroids/view/planar/entity/bullet.hpp>
#include <sgeroids/view/planar/entity/spaceship.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_shared_ptr.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/load_exn.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/sprite/make_vertex_format.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/intrusive/process/ordered_with_options.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/options_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/matrix/identity.hpp>
#include <fcppt/math/matrix/output.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <algorithm>
#include <functional>
#include <typeinfo>
#include <utility>
#include <fcppt/config/external_end.hpp>


sgeroids::view::planar::object::object(
	fcppt::log::context &_log_context,
	sge::renderer::device::ffp &_renderer,
	sge::font::system &_font_system,
	sge::image2d::system &_image_system,
	sge::audio::loader &_audio_loader,
	sge::audio::player &_audio_player)
:
	log_{
		_log_context,
		sgeroids::log_location(),
		sgeroids::log_parameters(
			fcppt::log::name{
				FCPPT_TEXT("view")
			}
		)
	},
	renderer_(
		_renderer),
	audio_player_(
		_audio_player),
	rng_(
		sgeroids::random_generator_seed()),
	texture_tree_(
		sgeroids::media_path() / FCPPT_TEXT("images"),
		sgeroids::view::planar::texture_tree::path_to_resource_function{
			std::bind(
				&object::create_texture_from_path,
				this,
				std::ref(
					_image_system),
				std::placeholders::_1
			)
		},
		rng_
	),
	audio_buffer_tree_(
		sgeroids::media_path() / FCPPT_TEXT("sounds"),
		sgeroids::view::planar::audio_buffer_tree::path_to_resource_function{
			std::bind(
				&object::create_audio_buffer_from_path,
				this,
				std::ref(
					_audio_loader),
				std::placeholders::_1
			)
		},
		rng_
	),
	firing_sound_(
		audio_buffer_tree_.get(
			sge::resource_tree::path() / FCPPT_TEXT("lazor")
		)->create_nonpositional(
			sge::audio::sound::nonpositional_parameters())),
	sprite_vertex_declaration_(
		renderer_.create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::sprite::make_vertex_format<planar::sprite::choices>()))),
	dynamic_buffers_(
		sge::sprite::buffers::parameters(
			renderer_,
			*sprite_vertex_declaration_),
		sge::sprite::buffers::option::dynamic),
	dynamic_collection_(),
	sprite_state_(
		renderer_,
		sge::sprite::state::parameters<
			sprite_state_choices
		>()),
	projection_matrix_(
		fcppt::math::matrix::identity<
			sge::renderer::matrix4
		>()
	),
	entities_(),
	background_(),
	particles_(),
	score_font_(
		_font_system.create_font(
			sge::font::parameters()
			.family(
				FCPPT_TEXT(
					"cursive"))
			.ttf_size(
				sge::font::ttf_size(
					40)))),
	score_text_()
{
}

void
sgeroids::view::planar::object::add_spaceship(
	model::entity_id const &_id,
	model::radius const &_radius,
	model::player_name const &_player_name)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("Adding spaceship"));

	entities_.emplace(
		_id.get(),
		fcppt::unique_ptr_to_base<
			sgeroids::view::planar::entity::base
		>(
			fcppt::make_unique_ptr<
				entity::spaceship
			>(
				dynamic_collection_,
				texture_tree_,
				audio_buffer_tree_,
				planar::callbacks::add_particle(
					std::bind(
						&object::add_particle,
						this,
						std::placeholders::_1,
						std::placeholders::_2,
						std::placeholders::_3)),
				rng_,
				planar::radius_to_screen_space(
					_radius),
				sgeroids::view::planar::player_name(
					sge::charconv::utf8_string_to_fcppt(
						_player_name.get()
					)
				)
			)
		)
	);
}

void
sgeroids::view::planar::object::add_asteroid(
	model::entity_id const &_id,
	model::radius const &_radius)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("Adding asteroid with radius \"")
			<< _radius.get()
			<< FCPPT_TEXT("\""));

	entities_.emplace(
		_id.get(),
		fcppt::unique_ptr_to_base<
			sgeroids::view::planar::entity::base
		>(
			fcppt::make_unique_ptr<entity::asteroid>(
				dynamic_collection_,
				texture_tree_,
				planar::radius_to_screen_space(
					_radius))));
}

void
sgeroids::view::planar::object::add_projectile(
	model::entity_id const &_id)
{
	firing_sound_->play(
		sge::audio::sound::repeat::once);

	entities_.emplace(
		_id.get(),
		fcppt::unique_ptr_to_base<
			sgeroids::view::planar::entity::base
		>(
			fcppt::make_unique_ptr<entity::bullet>(
				dynamic_collection_,
				texture_tree_)));
}

void
sgeroids::view::planar::object::add_particle(
	planar::position const &_position,
	particle::velocity const &_velocity,
	particle::lifespan const &_lifespan)
{
	particles_.push_back(
		particle::object(
			dynamic_collection_,
			texture_tree_,
			_position,
			_velocity,
			_lifespan));
}

void
sgeroids::view::planar::object::collide_projectile_asteroid(
	model::projectile_id const &,
	model::asteroid_id const &)
{
}

void
sgeroids::view::planar::object::score_change(
	model::spaceship_id const &_id,
	model::score const &_score)
{
	entity_map::iterator it =
		entities_.find(
			_id.get());

	if(it == entities_.end())
	{
		FCPPT_LOG_DEBUG(
			log_,
			fcppt::log::_ <<
				FCPPT_TEXT("view: score_change: unknown entity id ")+
					fcppt::insert_to_fcppt_string(
						_id.get()));
		return;
	}

	fcppt::optional::maybe(
		fcppt::cast::dynamic<entity::spaceship>(
			*(it->second)
		),
		[
			this,
			_id
		]{
			FCPPT_LOG_DEBUG(
				log_,
				fcppt::log::_ <<
					FCPPT_TEXT("view: score_change: not a spaceship: id ")+
						fcppt::insert_to_fcppt_string(
							_id.get()));
		},
		[
			_score,
			this
		](
			fcppt::reference<
				entity::spaceship
			> const _maybe_a_ship
		)
		{
			score_text_ =
				optional_static_text(
					sge::font::draw::static_text(
						renderer_,
						*score_font_,
						sge::font::from_fcppt_string(
							fcppt::insert_to_fcppt_string(
								_maybe_a_ship.get().player_name())) +
						SGE_FONT_LIT(": ") +
						sge::font::from_fcppt_string(
							fcppt::insert_to_fcppt_string(
								_score.get())),
						sge::font::text_parameters(
							sge::font::align_h::variant(
								sge::font::align_h::left())),
						sge::font::vector(
							0,
							0
						),
						sge::image::color::any::object{
							sge::image::color::predef::white()
						},
						sge::renderer::texture::emulate_srgb::no
					)
				);
		}
	);
}

void
sgeroids::view::planar::object::destroy_asteroid(
	model::entity_id const &)
{
}

void
sgeroids::view::planar::object::remove_entity(
	model::entity_id const &_id)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("Removing entity"));

	entity_map::size_type const erased_elements =
		entities_.erase(
			_id.get());

	if(erased_elements != 1u)
		throw
			sgeroids::exception(
				FCPPT_TEXT("remove_entity: The entity with id ")+
				fcppt::insert_to_fcppt_string(
					_id.get())+
				FCPPT_TEXT(" was erased ")+
				fcppt::insert_to_fcppt_string(
					erased_elements)+
				FCPPT_TEXT(" times."));
}

void
sgeroids::view::planar::object::position_entity(
	model::entity_id const &_id,
	model::position const &_position)
{
	entity::base &e =
		this->search_entity(
			_id,
			planar::error_context(
				FCPPT_TEXT("position_entity")));

	e.position(
		planar::position(
			_position.get()));
}

void
sgeroids::view::planar::object::rotation_entity(
	model::entity_id const &_id,
	model::rotation const &_rotation)
{
	/*
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("New rotation for entity ")
			<< _id.get()
			<< FCPPT_TEXT(": ")
			<< _rotation.get());
			*/

	entity::base &e =
		this->search_entity(
			_id,
			planar::error_context(
				FCPPT_TEXT("rotation_entity")));

	e.rotation(
		planar::rotation_to_screen_space(
			_rotation));
}

void
sgeroids::view::planar::object::change_thrust(
	model::entity_id const &_id,
	model::thrust const &_thrust)
{
	entity_map::iterator it =
		entities_.find(
			_id.get());

	if(it == entities_.end())
		throw
			sgeroids::exception(
				FCPPT_TEXT("view: change_thrust: unknown entity id ")+
				fcppt::insert_to_fcppt_string(
					_id.get()));

	fcppt::optional::to_exception(
		fcppt::cast::dynamic<entity::spaceship>(
			*(it->second)
		),
		[
			_id,
			it
		]{
			auto const &entity(
				*it->second
			);

			return
				sgeroids::exception{
					FCPPT_TEXT("view: change_thrust: The entity id ")+
					fcppt::insert_to_fcppt_string(
						_id.get())+
					FCPPT_TEXT(" refers to an entity of (invalid) type ")+
					fcppt::type_name_from_info(
						typeid(
							entity
						)
					)
				};
		}
	).get().change_thrust(
		 _thrust);
}

void
sgeroids::view::planar::object::play_area(
	sgeroids::model::play_area const &_area)
{
	background_ =
		optional_background_unique_ptr(
			fcppt::make_unique_ptr<
				background::object
			>(
				renderer_,
				*sprite_vertex_declaration_,
				texture_tree_,
				_area,
				rng_,
				background::star_size(3500),
				background::star_count(500u)
			)
		);

	projection_matrix_ =
		sge::renderer::projection::orthogonal(
			fcppt::math::box::structure_cast<
				sge::renderer::projection::rect,
				fcppt::cast::int_to_float_fun
			>(
				_area.get()),
			// 0 and 10 are just guesses
			sge::renderer::projection::near(
				-10.f),
			sge::renderer::projection::far(
				10.f));
}

void
sgeroids::view::planar::object::update()
{
	for(
		entity_map::iterator it =
			entities_.begin();
		it != entities_.end();
		++it)
		it->second->update();

	for(
		particle_vector::iterator it =
			particles_.begin();
		it !=
			particles_.end();)
	{
		it->update();
		if (it->dead())
			it = particles_.erase(it);
		else
			++it;
	}
}

void
sgeroids::view::planar::object::render(
	sge::renderer::context::ffp &_render_context)
{
	_render_context.clear(
		sge::renderer::clear::parameters()
		.back_buffer(
			sge::image::color::any::object{
				sge::image::color::predef::black()
			}
		)
	);

	sge::renderer::state::ffp::transform::object_unique_ptr const transform_state(
		renderer_.create_transform_state(
			sge::renderer::state::ffp::transform::parameters(
				projection_matrix_)));

	sge::renderer::state::ffp::transform::scoped const projection_transform(
		_render_context,
		sge::renderer::state::ffp::transform::mode::projection,
		*transform_state);

	fcppt::optional::maybe_void(
		background_,
		[
			&_render_context
		](
			auto const &_background
		)
		{
			_background->render(
				_render_context
			);
		}
	);

	sge::sprite::intrusive::process::ordered_with_options
	<
		sge::sprite::process::options
		<
			sge::sprite::process::geometry_options::sort_and_update
		>
	>(
		_render_context,
		dynamic_collection_,
		dynamic_buffers_,
		sprite_state_,
		sge::sprite::compare::default_(),
		sge::sprite::state::options<
			sprite_state_choices
		>(
			sge::sprite::state::vertex_options::declaration));

	fcppt::optional::maybe_void(
		score_text_,
		[
			&_render_context
		](
			sge::font::draw::static_text &_score_text
		)
		{
			_score_text.draw(
				_render_context
			);
		}
	);
}

void
sgeroids::view::planar::object::gameover()
{
}

sgeroids::view::planar::object::~object()
{
}

sge::texture::const_part_shared_ptr const
sgeroids::view::planar::object::create_texture_from_path(
	sge::image2d::system &_image_loader,
	boost::filesystem::path const &_path)
{
	return
		sge::texture::const_part_shared_ptr(
			fcppt::make_shared_ptr<
				sge::texture::part_raw_ptr>(
				sge::renderer::texture::create_planar_from_path(
					_path,
					renderer_,
					_image_loader,
					sge::renderer::texture::mipmap::off(),
					sge::renderer::resource_flags_field::null(),
					sge::renderer::texture::emulate_srgb::yes)));

}

sge::audio::buffer_shared_ptr const
sgeroids::view::planar::object::create_audio_buffer_from_path(
	sge::audio::loader &_audio_loader,
	boost::filesystem::path const &_path)
{
	return
		sge::audio::buffer_shared_ptr(
			audio_player_.create_buffer(
				*sge::audio::load_exn(
					_audio_loader,
					_path
				)
			)
		);

}

sgeroids::view::planar::entity::base &
sgeroids::view::planar::object::search_entity(
	model::entity_id const &_id,
	planar::error_context const &_error_context)
{
	entity_map::iterator const it =
		entities_.find(
			_id.get());

	if(it == entities_.end())
		throw
			sgeroids::exception(
				FCPPT_TEXT("view: ")+
				_error_context.get()+
				FCPPT_TEXT(": The entity with id ")+
				fcppt::insert_to_fcppt_string(
					_id.get())+
				FCPPT_TEXT(" could not be found."));

	return
		*(it->second);
}
