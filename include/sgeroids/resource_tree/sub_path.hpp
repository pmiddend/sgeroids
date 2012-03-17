#ifndef SGEROIDS_RESOURCE_TREE_SUB_PATH_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_SUB_PATH_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace resource_tree
{
FCPPT_MAKE_STRONG_TYPEDEF(
	boost::filesystem::path,
	sub_path);
}
}

#endif
