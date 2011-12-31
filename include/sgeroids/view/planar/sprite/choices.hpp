#ifndef SGEROIDS_VIEW_PLANAR_SPRITE_CHOICES_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_SPRITE_CHOICES_HPP_INCLUDED

#include <sgeroids/view/planar/sprite/type_choices.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_rotation.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/intrusive/tag.hpp>
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
sge::sprite::choices
<
	sprite::type_choices,
	boost::mpl::vector5
	<
		sge::sprite::with_color,
		sge::sprite::with_texture,
		sge::sprite::with_dim,
		sge::sprite::with_rotation,
		sge::sprite::intrusive::tag
	>
>
choices;
}
}
}
}

#endif
