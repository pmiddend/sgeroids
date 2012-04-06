#include <sge/sprite/process/options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/intrusive/process/ordered_with_options.hpp>
#include <sge/sprite/render/options.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/make_vertex_format.hpp>
#include <sgeroids/exception.hpp>
#include <sgeroids/media_path.hpp>
#include <sgeroids/random_generator_seed.hpp>
#include <sgeroids/view/log.hpp>
#include <sgeroids/view/planar/object.hpp>
#include <sgeroids/view/planar/radius_to_screen_space.hpp>
#include <sgeroids/view/planar/rotation_to_screen_space.hpp>
#include <sgeroids/view/planar/entity/asteroid.hpp>
#include <sgeroids/view/planar/entity/bullet.hpp>
#include <sgeroids/view/planar/entity/spaceship.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_dynamic_cast.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/container/ptr/insert_unique_ptr.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/matrix/output.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <algorithm>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


sgeroids::view::planar::object::object(
	sge::renderer::device &_renderer,
	sge::font::system &,
	sge::image2d::system &_image_system,
	sge::audio::loader &_audio_loader,
	sge::audio::player &_audio_player)
:
	renderer_(
		_renderer),
	audio_player_(
		_audio_player),
	rng_(
		sgeroids::random_generator_seed()),
	texture_manager_(
		std::tr1::bind(
			&object::create_new_texture_callback,
			this)),
	texture_tree_(
		sgeroids::media_path() / FCPPT_TEXT("images"),
		std::tr1::bind(
			&object::create_texture_from_path,
			this,
			fcppt::ref(
				_image_system),
			std::tr1::placeholders::_1),
		rng_),
	audio_buffer_tree_(
		sgeroids::media_path() / FCPPT_TEXT("sounds"),
		std::tr1::bind(
			&object::create_audio_buffer_from_path,
			this,
			fcppt::ref(
				_audio_loader),
			std::tr1::placeholders::_1),
		rng_),
	firing_sound_(
		audio_buffer_tree_.get(
			sgeroids::resource_tree::path() / FCPPT_TEXT("lazor")
		)->create_nonpositional(
			sge::audio::sound::nonpositional_parameters())),
	sprite_vertex_declaration_(
		renderer_.create_vertex_declaration(
			sge::sprite::make_vertex_format<planar::sprite::choices>())),
	dynamic_buffers_(
		sge::sprite::buffers::parameters(
			renderer_,
			*sprite_vertex_declaration_),
		sge::sprite::buffers::option::dynamic),
	dynamic_collection_(),
	projection_matrix_(),
	entities_(),
	background_(),
	particles_()
{
}

void
sgeroids::view::planar::object::add_spaceship(
	model::entity_id const &_id,
	model::radius const &_radius,
	model::player_name const &_name)
{
	FCPPT_LOG_DEBUG(
		view::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Adding spaceship with player name \"")
			<< _name.get()
			<< FCPPT_TEXT("\""));

	fcppt::container::ptr::insert_unique_ptr_map(
		entities_,
		_id.get(),
		fcppt::make_unique_ptr<entity::spaceship>(
			fcppt::ref(dynamic_collection_),
			fcppt::ref(texture_tree_),
			fcppt::ref(audio_player_),
			fcppt::ref(audio_buffer_tree_),
			planar::callbacks::add_particle(
				std::tr1::bind(
					&object::add_particle,
					this,
					std::tr1::placeholders::_1,
					std::tr1::placeholders::_2,
					std::tr1::placeholders::_3)),
			fcppt::ref(rng_),
			planar::radius_to_screen_space(
				_radius)));
}

void
sgeroids::view::planar::object::add_asteroid(
	model::entity_id const &_id,
	model::radius const &_radius)
{
	FCPPT_LOG_DEBUG(
		view::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Adding asteroid with radius \"")
			<< _radius.get()
			<< FCPPT_TEXT("\""));

	fcppt::container::ptr::insert_unique_ptr_map(
		entities_,
		_id.get(),
		fcppt::make_unique_ptr<entity::asteroid>(
			fcppt::ref(
				dynamic_collection_),
			fcppt::ref(
				texture_tree_),
			planar::radius_to_screen_space(
				_radius)));
}

void
sgeroids::view::planar::object::add_projectile(
	model::entity_id const &_id)
{
	firing_sound_->play(
		sge::audio::sound::repeat::once);
	fcppt::container::ptr::insert_unique_ptr_map(
		entities_,
		_id.get(),
		fcppt::make_unique_ptr<entity::bullet>(
			fcppt::ref(
				dynamic_collection_),
			fcppt::ref(
				texture_tree_)));
}

void
sgeroids::view::planar::object::add_particle(
	planar::position const &_position,
	particle::velocity const &_velocity,
	particle::lifespan const &_lifespan)
{
	particles_.push_back(
		new particle::object(
			fcppt::ref(
				dynamic_collection_),
			fcppt::ref(
				texture_tree_),
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
	model::score const &)
{
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
		view::log(),
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
		view::log(),
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

	fcppt::optional<entity::spaceship &> maybe_a_ship(
		fcppt::optional_dynamic_cast<entity::spaceship &>(
			*(it->second)));

	 if(!maybe_a_ship)
			sgeroids::exception(
				FCPPT_TEXT("view: change_thrust: The entity id ")+
				fcppt::insert_to_fcppt_string(
					_id.get())+
				FCPPT_TEXT(" refers to an entity of (invalid) type ")+
				fcppt::type_name(
					typeid(
						*(it->second))));

	 maybe_a_ship->change_thrust(
		 _thrust);
}

void
sgeroids::view::planar::object::play_area(
	sgeroids::model::play_area const &_area)
{
	background_.reset(
		new background::object(
			renderer_,
			*sprite_vertex_declaration_,
			texture_tree_,
			_area,
			rng_,
			background::star_size(3500),
			background::star_count(500u)));

	projection_matrix_ =
		sge::renderer::projection::orthogonal(
			fcppt::math::box::structure_cast<sge::renderer::projection::rect>(
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
sgeroids::view::planar::object::render()
{
	sge::renderer::state::scoped scoped_states(
		renderer_,
		sge::renderer::state::list
			(sge::renderer::state::color::back_buffer_clear_color = sge::image::colors::black())
			(sge::renderer::state::cull_mode::off)
			(sge::renderer::state::depth_func::off));

	renderer_.clear(
		sge::renderer::clear_flags_field(
			sge::renderer::clear_flags::back_buffer));

	sge::renderer::scoped_transform world_transform(
		renderer_,
		sge::renderer::matrix_mode::world,
		sge::renderer::matrix4::identity());

	sge::renderer::scoped_transform projection_transform(
		renderer_,
		sge::renderer::matrix_mode::projection,
		projection_matrix_);

	background_->render();

	sge::sprite::intrusive::process::ordered_with_options
	<
		sge::sprite::process::options
		<
			sge::sprite::process::geometry_options::sort_and_update,
			sge::sprite::render::options
			<
				sge::sprite::render::matrix_options::nothing,
				sge::sprite::render::state_options::set,
				sge::sprite::render::vertex_options::declaration
			>
		>
	>(
		dynamic_collection_,
		dynamic_buffers_,
		sge::sprite::compare::default_());
}

void
sgeroids::view::planar::object::gameover()
{
}

sgeroids::view::planar::object::~object()
{
}

sge::texture::fragmented_unique_ptr
sgeroids::view::planar::object::create_new_texture_callback()
{
	return
		sge::texture::fragmented_unique_ptr(
			fcppt::make_unique_ptr<sge::texture::no_fragmented>(
				fcppt::ref(
					renderer_),
				// Using this color format for the textures is pure
				// convention. We need an r,g,b and an alpha channel,
				// but maybe argb8 or something would be better.
				sge::image::color::format::rgba8,
				// This is just guesswork. Maybe mipmaps would be
				// better (especially since we're using no_fragmented
				// here, which doesn't suffer from "bleeding" artefacts
				// like the atlased texture).
				sge::renderer::texture::mipmap::off()));
}

sge::texture::const_part_shared_ptr const
sgeroids::view::planar::object::create_texture_from_path(
	sge::image2d::system &_image_loader,
	boost::filesystem::path const &_path)
{
	return
		sge::texture::const_part_shared_ptr(
			sge::texture::add_image(
				texture_manager_,
				*_image_loader.load(
					_path)));

}

sge::audio::buffer_shared_ptr const
sgeroids::view::planar::object::create_audio_buffer_from_path(
	sge::audio::loader &_audio_loader,
	boost::filesystem::path const &_path)
{
	return
		sge::audio::buffer_shared_ptr(
			audio_player_.create_buffer(
				*_audio_loader.load(
					_path)));

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
