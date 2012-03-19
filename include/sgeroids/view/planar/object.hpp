#ifndef SGEROIDS_VIEW_PLANAR_OBJECT_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_OBJECT_HPP_INCLUDED

#include <sgeroids/random_generator.hpp>
#include <sgeroids/resource_tree/object.hpp>
#include <sgeroids/view/base.hpp>
#include <sgeroids/view/planar/audio_buffer_tree.hpp>
#include <sgeroids/view/planar/error_context.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/background/object.hpp>
#include <sgeroids/view/planar/entity/base_fwd.hpp>
#include <sgeroids/view/planar/particle/object.hpp>
#include <sgeroids/view/planar/sprite/ordered_collection.hpp>
#include <sgeroids/view/planar/sprite/dynamic_buffers.hpp>
#include <sge/audio/buffer_ptr.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/sound/base_ptr.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/texture/fragmented_unique_ptr.hpp>
#include <sge/texture/manager.hpp>
#include <sge/sprite/intrusive/ordered/collection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace view
{
namespace planar
{
/**
\brief Represents a 2D, sprite-oriented view

This is the "main" view class and is instantiated when the game is started. It
currently is <em>directly</em> responsible for:

<ul>
	<li>
		Rendering the dynamic sprites. This encompasses everything that
		might move/rotate each frame. The background, for example, is
		managed separately (in
		sgeroids::view::planar::background::object).
	</li>
	<li>
		Owning a random number generator that's private to the view.
		This is used for random effects such as explosions.
	</li>
	<li>
		Loading and providing access to sounds and textures.
	</li>
	<li>
		Maintaining the current projection matrix (which transfers from game coordinates to screen coordinates).
	</li>
	<li>
		Owning the sprite vertex declaration (somebody's gotta do it).
	</li>
</ul>
*/
class object
:
	public view::base
{
FCPPT_NONCOPYABLE(
	object);
public:
	explicit
	object(
		sge::renderer::device &,
		sge::font::system &,
		sge::image2d::system &,
		sge::audio::loader &,
		sge::audio::player &);

	void
	add_spaceship(
		model::entity_id const &,
		model::radius const &,
		model::player_name const &);

	void
	add_asteroid(
		model::entity_id const &,
		model::radius const &);

	void
	add_projectile(
		model::entity_id const &);

	void
	add_particle(
		planar::position const &,
		particle::velocity const &,
		particle::lifespan const &);

	void
	collide_projectile_asteroid(
		model::projectile_id const &,
		model::asteroid_id const &);

	void
	score_change(
		model::score const &);

	void
	destroy_asteroid(
		model::entity_id const &);

	void
	remove_entity(
		model::entity_id const &);

	void
	position_entity(
		model::entity_id const &,
		model::position const &);

	void
	rotation_entity(
		model::entity_id const &,
		model::rotation const &);

	void
	change_thrust(
		model::entity_id const &,
		model::thrust const &);

	void
	play_area(
		sgeroids::model::play_area const &);

	void
	gameover();

	void
	update();

	void
	render();

	~object();
private:
	typedef
	boost::ptr_map<model::entity_id::value_type,entity::base>
	entity_map;

	typedef
	boost::ptr_vector<particle::object>
	particle_vector;

	sge::renderer::device &renderer_;
	sge::audio::player &audio_player_;
	sgeroids::random_generator rng_;
	sge::texture::manager texture_manager_;
	planar::texture_tree texture_tree_;
	planar::audio_buffer_tree audio_buffer_tree_;
	sge::audio::sound::base_ptr firing_sound_;
	sge::renderer::vertex_declaration_ptr sprite_vertex_declaration_;
	planar::sprite::dynamic_buffers dynamic_buffers_;
	planar::sprite::ordered_collection dynamic_collection_;
	sge::renderer::matrix4 projection_matrix_;
	entity_map entities_;
	fcppt::unique_ptr<background::object> background_;
	particle_vector particles_;

	/**
	\brief This function is called by the texture manager whenever it needs to allocate a new texture.
	*/
	sge::texture::fragmented_unique_ptr
	create_new_texture_callback();

	/**
	\brief This function is called by the texture tree to create a texture resource out of a path
	*/
	sge::texture::const_part_ptr const
	create_texture_from_path(
		sge::image2d::system &,
		boost::filesystem::path const &);

	/**
	\brief This function is called by the audio buffer tree to create an audio buffer out of a path
	*/
	sge::audio::buffer_ptr const
	create_audio_buffer_from_path(
		sge::audio::loader &,
		boost::filesystem::path const &);

	/**
	\brief Helper function to search and return an entity by the id

	The error context will tell the user of the crashed program which
	operation failed.
	*/
	entity::base &
	search_entity(
		model::entity_id const &,
		planar::error_context const &);
};
}
}
}

#endif
