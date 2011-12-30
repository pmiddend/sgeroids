#ifndef SGEROIDS_VIEW_PLANAR_SPRITE_TYPE_CHOICES_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_SPRITE_TYPE_CHOICES_HPP_INCLUDED

#include <sge/sprite/type_choices.hpp>
#include <sgeroids/view/planar/sprite/color_format.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
namespace sprite
{
typedef
sge::sprite::type_choices
<
	int,
	float,
	sprite::color_format
>
type_choices;
}
}
}
}

#endif
