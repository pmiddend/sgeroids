#ifndef SGEROIDS_VIEW_PLANAR_SPRITE_ORDERED_COLLECTION_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_SPRITE_ORDERED_COLLECTION_HPP_INCLUDED

#include <sgeroids/view/planar/sprite/choices.hpp>
#include <sgeroids/view/planar/sprite/order.hpp>
#include <sge/sprite/intrusive/ordered_collection_fwd.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
namespace sprite
{
/**
\brief A container for sprites consisting of multiple layers.

The sprite layers are called "orders".
*/
typedef
sge::sprite::intrusive::ordered_collection
<
	planar::sprite::choices,
	planar::sprite::order
>
ordered_collection;
}
}
}
}

#endif
