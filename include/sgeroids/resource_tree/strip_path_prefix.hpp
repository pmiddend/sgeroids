#ifndef SGEROIDS_RESOURCE_TREE_STRIP_PATH_PREFIX_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_STRIP_PATH_PREFIX_HPP_INCLUDED

#include <sgeroids/resource_tree/base_path.hpp>
#include <sgeroids/resource_tree/path.hpp>
#include <sgeroids/resource_tree/sub_path.hpp>


namespace sgeroids
{
namespace resource_tree
{
resource_tree::path const
strip_path_prefix(
	resource_tree::base_path const &,
	resource_tree::sub_path const &);
}
}

#endif
