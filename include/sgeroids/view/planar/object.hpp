#ifndef SGEROIDS_VIEW_PLANAR_OBJECT_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_OBJECT_HPP_INCLUDED

#include <sgeroids/random_generator.hpp>
#include <sgeroids/view/base.hpp>
#include <sgeroids/view/planar/audio_buffer_tree.hpp>
#include <sgeroids/view/planar/error_context.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/background/object.hpp>
#include <sgeroids/view/planar/entity/base_fwd.hpp>
#include <sgeroids/view/planar/particle/object.hpp>
#include <sgeroids/view/planar/sprite/dynamic_buffers.hpp>
#include <sgeroids/view/planar/sprite/ordered_collection.hpp>
#include <sge/audio/buffer_shared_ptr.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/sprite/state/choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/with_blend.hpp>
#include <sge/sprite/state/with_rasterizer.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <map>
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
	object(
		sge::renderer::device::ffp &,
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
		model::spaceship_id const &,
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
	render(
		sge::renderer::context::ffp &);

	~object();
private:
	typedef
	std::map<
		model::entity_id::value_type,
		fcppt::unique_ptr<
			entity::base
		>
	>
	entity_map;

	typedef
	std::vector<particle::object>
	particle_vector;

	typedef
	sge::sprite::state::choices
	<
		boost::mpl::vector2
		<
			sge::sprite::state::with_blend,
			sge::sprite::state::with_rasterizer
		>
	>
	sprite_state_choices;

	typedef
	sge::sprite::state::object
	<
		sprite_state_choices
	>
	sprite_state;

	sge::renderer::device::ffp &renderer_;
	sge::audio::player &audio_player_;
	sgeroids::random_generator rng_;
	planar::texture_tree texture_tree_;
	planar::audio_buffer_tree audio_buffer_tree_;
	sge::audio::sound::base_unique_ptr const firing_sound_;
	sge::renderer::vertex::declaration_unique_ptr const sprite_vertex_declaration_;
	planar::sprite::dynamic_buffers dynamic_buffers_;
	planar::sprite::ordered_collection dynamic_collection_;
	sprite_state sprite_state_;
	sge::renderer::matrix4 projection_matrix_;
	entity_map entities_;

	typedef
	fcppt::optional::object<
		fcppt::unique_ptr<
			background::object
		>
	>
	optional_background_unique_ptr;

	optional_background_unique_ptr background_;

	particle_vector particles_;
	sge::font::object_unique_ptr score_font_;

	typedef
	fcppt::optional::object<
		sge::font::draw::static_text
	>
	optional_static_text;

	optional_static_text score_text_;

	/**
	\brief This function is called by the texture tree to create a texture resource out of a path
	*/
	sge::texture::const_part_shared_ptr const
	create_texture_from_path(
		sge::image2d::system &,
		boost::filesystem::path const &);

	/**
	\brief This function is called by the audio buffer tree to create an audio buffer out of a path
	*/
	sge::audio::buffer_shared_ptr const
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
