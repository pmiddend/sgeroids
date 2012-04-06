#ifndef SGEROIDS_VIEW_PLANAR_AUDIO_BUFFER_TREE_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_AUDIO_BUFFER_TREE_HPP_INCLUDED

#include <sgeroids/resource_tree/object_fwd.hpp>
#include <sge/audio/buffer_shared_ptr.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
typedef
sgeroids::resource_tree::object
<
	sge::audio::buffer_shared_ptr
>
audio_buffer_tree;
}
}
}

#endif
