#ifndef SGEROIDS_VIEW_PLANAR_SPRITE_TYPE_CHOICES_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_SPRITE_TYPE_CHOICES_HPP_INCLUDED

#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/float_type.hpp>


namespace sgeroids
{
namespace view
{
namespace planar
{
namespace sprite
{
typedef
sge::sprite::config::type_choices
<
	sge::sprite::config::unit_type<int>,
	sge::sprite::config::float_type<float>
>
type_choices;
}
}
}
}

#endif
