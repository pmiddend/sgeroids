#ifndef SGEROIDS_VIEW_BACKGROUND_OBJECT_HPP_INCLUDED
#define SGEROIDS_VIEW_BACKGROUND_OBJECT_HPP_INCLUDED

#include <sgeroids/model/play_area.hpp>
#include <sgeroids/random_generator.hpp>
#include <sgeroids/view/planar/sprite/object.hpp>
#include <sgeroids/view/planar/sprite/system.hpp>
#include <sgeroids/view/planar/sprite/system_impl.hpp>
#include <sgeroids/resource_tree/object.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
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
	explicit
	object(
		sgeroids::view::planar::sprite::system &,
		sgeroids::view::planar::texture_tree &,
		sgeroids::model::play_area const &,
		sgeroids::random_generator &);


private:
	typedef
	boost::ptr_vector<sgeroids::view::planar::sprite::object>
	sprite_container;

	sprite_container sprites_;
	sgeroids::view::planar::sprite::system &sprite_system_;
	sgeroids::view::planar::texture_tree &texture_tree_;
	sgeroids::model::play_area play_area_;
	sgeroids::random_generator rng_;

};
}
}
}
}
#endif
