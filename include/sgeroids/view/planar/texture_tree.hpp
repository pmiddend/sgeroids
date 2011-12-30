#ifndef SGEROIDS_VIEW_PLANAR_TEXTURE_TREE_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_TEXTURE_TREE_HPP_INCLUDED

#include <sgeroids/resource_tree/object_fwd.hpp>
#include <sge/texture/const_part_ptr.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
typedef
sgeroids::resource_tree::object<sge::texture::const_part_ptr>
texture_tree;
}
}
}

#endif
