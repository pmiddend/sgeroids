#ifndef SGEROIDS_VIEW_PLANAR_SPRITE_CHOICES_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_SPRITE_CHOICES_HPP_INCLUDED

#include <sgeroids/view/planar/sprite/color_format.hpp>
#include <sgeroids/view/planar/sprite/type_choices.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/intrusive.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/config/with_rotation.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace view
{
namespace planar
{
namespace sprite
{
typedef
sge::sprite::config::choices
<
	sprite::type_choices,
	sge::sprite::config::pos
	<
		sge::sprite::config::pos_option::center
	>,
	sge::sprite::config::normal_size
	<
		sge::sprite::config::texture_size_option::never
	>,
	boost::mpl::vector4
	<
		sge::sprite::config::with_texture
		<
			sge::sprite::config::texture_level_count<1u>,
			sge::sprite::config::texture_coordinates::automatic,
			sge::sprite::config::texture_ownership::shared
		>,
		sge::sprite::config::with_rotation,
		sge::sprite::config::with_color
		<
			planar::sprite::color_format
		>,
		sge::sprite::config::intrusive
	>
>
choices;
}
}
}
}

#endif
