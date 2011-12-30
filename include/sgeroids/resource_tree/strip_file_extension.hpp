#ifndef SGEROIDS_RESOURCE_TREE_STRIP_FILE_EXTENSION_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_STRIP_FILE_EXTENSION_HPP_INCLUDED

#include <sgeroids/resource_tree/path.hpp>

namespace sgeroids
{
namespace resource_tree
{
/**
\brief Modify a path, stripping the file extension at the end
*/
resource_tree::path const
strip_file_extension(
	resource_tree::path const &);
}
}

#endif
