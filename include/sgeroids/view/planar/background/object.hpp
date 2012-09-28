#ifndef SGEROIDS_VIEW_PLANAR_BACKGROUND_OBJECT_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_BACKGROUND_OBJECT_HPP_INCLUDED

#include <sgeroids/random_generator_fwd.hpp>
#include <sgeroids/model/play_area.hpp>
#include <sgeroids/view/planar/texture_tree_fwd.hpp>
#include <sgeroids/view/planar/background/star_count.hpp>
#include <sgeroids/view/planar/background/star_size.hpp>
#include <sgeroids/view/planar/sprite/dynamic_buffers.hpp>
#include <sgeroids/view/planar/sprite/object.hpp>
#include <sgeroids/view/planar/sprite/ordered_collection.hpp>
#include <sgeroids/view/planar/sprite/static_range.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/sprite/intrusive/ordered/collection_decl.hpp>
#include <sge/sprite/render/range_decl.hpp>
#include <sge/sprite/state/choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/with_blend.hpp>
#include <sge/sprite/state/with_rasterizer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace view
{
namespace planar
{
namespace background
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	/**
	\brief Initializes the view

	Note that initialization of the view shouldn't directly use the json
	config file. Instead, all relevant parameters are passed directly, such
	as the star size and count.
	*/
	object(
		sge::renderer::device::core &,
		sge::renderer::vertex_declaration const &,
		sgeroids::view::planar::texture_tree &,
		sgeroids::model::play_area const &,
		sgeroids::random_generator &,
		star_size,
		star_count);

	/**
	\brief Render the background sprites

	\warning
	This function assumes that the sprite projection matrices are set from
	the _outside_ (by sgeroids::view::planar::object::render currently).
	*/
	void
	render(
		sge::renderer::context::core &);

	~object();
private:
	typedef
	std::vector
	<
		sgeroids::view::planar::sprite::object
	>
	sprite_container;

	sgeroids::view::planar::sprite::dynamic_buffers sprite_buffers_;

	sgeroids::view::planar::sprite::ordered_collection sprite_collection_;

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

	sprite_state sprite_state_;

	sprite_container sprites_;

	sgeroids::view::planar::sprite::static_range sprite_render_range_;

	sgeroids::view::planar::texture_tree &texture_tree_;

	sgeroids::model::play_area const play_area_;

	background::star_size const star_size_;

	background::star_count const star_count_;

};
}
}
}
}
#endif
