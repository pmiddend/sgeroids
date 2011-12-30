#ifndef SGEROIDS_RESOURCE_TREE_SUB_PATH_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_SUB_PATH_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>
#include <fcppt/filesystem/path.hpp>


namespace sgeroids
{
namespace resource_tree
{
FCPPT_MAKE_STRONG_TYPEDEF(
	fcppt::filesystem::path,
	sub_path);
}
}

#endif
