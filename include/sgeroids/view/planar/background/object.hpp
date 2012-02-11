#ifndef SGEROIDS_VIEW_BACKGROUND_OBJECT_HPP_INCLUDED
#define SGEROIDS_VIEW_BACKGROUND_OBJECT_HPP_INCLUDED

#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <sgeroids/random_generator.hpp>
#include <sgeroids/model/play_area.hpp>
#include <sgeroids/resource_tree/object.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/background/star_count.hpp>
#include <sgeroids/view/planar/background/star_size.hpp>
#include <sgeroids/view/planar/sprite/dynamic_buffers.hpp>
#include <sgeroids/view/planar/sprite/object.hpp>
#include <sgeroids/view/planar/sprite/static_range.hpp>
#include <sgeroids/view/planar/sprite/ordered_collection.hpp>
#include <sge/sprite/intrusive/ordered/collection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
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
	explicit
	object(
		sge::renderer::device &,
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
	render();

	~object();
private:
	typedef
	boost::ptr_vector<sgeroids::view::planar::sprite::object>
	sprite_container;

	sgeroids::view::planar::sprite::dynamic_buffers sprite_buffers_;
	sgeroids::view::planar::sprite::ordered_collection sprite_collection_;
	sprite_container sprites_;
	sgeroids::view::planar::sprite::static_range sprite_render_range_;
	sgeroids::view::planar::texture_tree &texture_tree_;
	sgeroids::model::play_area const play_area_;
	sgeroids::random_generator rng_;
	background::star_size const star_size_;
	background::star_size const star_count_;

};
}
}
}
}
#endif
