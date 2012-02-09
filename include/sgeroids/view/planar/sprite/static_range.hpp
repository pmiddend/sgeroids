#ifndef SGEROIDS_VIEW_PLANAR_SPRITE_STATIC_RANGE_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_SPRITE_STATIC_RANGE_HPP_INCLUDED

#include <sgeroids/view/planar/sprite/choices.hpp>
#include <sge/sprite/render/range_fwd.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
namespace sprite
{
/**
\brief Represents a "compiled" range of sprites

Static ranges and dynamic ranges are handled slightly different in sprite. With
a dynamic range, you usually just construct your sprites, store them in a
collection and (basically!) call render(collection). This render call then
uploads the neccessary vertex data to the gpu and renders it.

With static sprites, you want to upload the vertex data only once (or
seldomly). So what you do is construct your sprites, add them to a collection
and then "compile" this collection into a vertex buffer and a "range" (this
type!). The range contains information about the way the buffer is rendered,
like when to switch the texture.
*/
typedef
sge::sprite::render::range<sprite::choices>
static_range;
}
}
}
}

#endif

