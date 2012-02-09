#ifndef SGEROIDS_VIEW_PLANAR_SPRITE_DYNAMIC_BUFFERS_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_SPRITE_DYNAMIC_BUFFERS_HPP_INCLUDED

#include <sgeroids/view/planar/sprite/choices.hpp>
// I'd like to use single_fwd here but that's not applicable. This is a
// typedef, hiding the real implementation. It would make no sense if you'd
// have to include the "real" implementation later on (and I'm too lazy for
// dynamic_buffers_fwd.hpp and dynamic_buffers_impl.hpp and so on)
#include <sge/sprite/buffers/single.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
namespace sprite
{
/**
\brief The "GPU storage unit" for dynamic sprites

This class is used to store the vertex buffers which represent vertex
information on the GPU.
*/
typedef
sge::sprite::buffers::single<sprite::choices>
dynamic_buffers;
}
}
}
}

#endif
