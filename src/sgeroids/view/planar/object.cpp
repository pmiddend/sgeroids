#include <typeinfo>
#include <fcppt/type_name.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/optional_dynamic_cast.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <sgeroids/exception.hpp>
#include <sgeroids/media_path.hpp>
#include <sgeroids/random_generator_seed.hpp>
#include <sgeroids/view/log.hpp>
#include <sgeroids/view/planar/object.hpp>
#include <sgeroids/view/planar/radius_to_screen_space.hpp>
#include <sgeroids/view/planar/rotation_to_screen_space.hpp>
#include <sgeroids/view/planar/entity/spaceship.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/system.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/render_states.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/matrix/output.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/tr1/functional.hpp>


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
	sprite_system_(
		renderer_),
	projection_matrix_(),
	entities_()
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
			fcppt::ref(
				sprite_system_),
			fcppt::ref(
				texture_tree_),
			planar::radius_to_screen_space(
				_radius)));
}

void
sgeroids::view::planar::object::add_asteroid(
	model::entity_id const &,
	model::radius const &)
{
}

void
sgeroids::view::planar::object::add_projectile(
	model::entity_id const &)
{
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
			sprite_system_,
			texture_tree_,
			_area,
			rng_,
			background::star_size(3500),
			background::star_count(500)));

	projection_matrix_ =
		sge::renderer::projection::orthogonal(
			fcppt::math::box::structure_cast<sge::renderer::projection::rect>(
				_area.get()),
			// 0 and 10 are just guesses
			sge::renderer::projection::near(
				-10),
			sge::renderer::projection::far(
				10));
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
}

void
sgeroids::view::planar::object::render()
{


	sge::renderer::state::scoped scoped_sprite_states(
		renderer_,
		sge::sprite::render_states<planar::sprite::choices>());

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

	sprite_system_.render_all_advanced(
		sge::sprite::default_equal());
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

sge::texture::const_part_ptr const
sgeroids::view::planar::object::create_texture_from_path(
	sge::image2d::system &_image_loader,
	fcppt::filesystem::path const &_path)
{
	return
		sge::texture::add_image(
			texture_manager_,
			*_image_loader.load(
				_path));

}

sge::audio::buffer_ptr const
sgeroids::view::planar::object::create_audio_buffer_from_path(
	sge::audio::loader &_audio_loader,
	fcppt::filesystem::path const &_path)
{
	return
		audio_player_.create_buffer(
			*_audio_loader.load(
				_path));

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
				_error_context.get()+
				FCPPT_TEXT("The entity with id ")+
				fcppt::insert_to_fcppt_string(
					_id.get())+
				FCPPT_TEXT(" could not be found."));

	return
		*(it->second);
}
