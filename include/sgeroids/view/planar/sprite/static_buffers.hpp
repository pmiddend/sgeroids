#ifndef SGEROIDS_VIEW_PLANAR_SPRITE_STATIC_BUFFERS_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_SPRITE_STATIC_BUFFERS_HPP_INCLUDED

#include <sgeroids/view/planar/sprite/choices.hpp>
// I'd like to use multi_fwd here but that's not applicable. This is a
// typedef, hiding the real implementation. It would make no sense if you'd
// have to include the "real" implementation later on (and I'm too lazy for
// static_buffers_fwd.hpp and static_buffers_impl.hpp and so on)
#include <sge/sprite/buffers/multi.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
namespace sprite
{
/**
\brief The "GPU storage unit" for static sprites

For a description of the rendering process for static sprites, see
sgeroids::view::planar::sprite::static_range.
*/
typedef
sge::sprite::buffers::multi<sprite::choices>
static_buffers;
}
}
}
}

#endif

