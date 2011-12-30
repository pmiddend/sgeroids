#ifndef SGEROIDS_RESOURCE_TREE_PATH_TO_RESOURCE_FUNCTION_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_PATH_TO_RESOURCE_FUNCTION_HPP_INCLUDED

#include <fcppt/filesystem/path.hpp>
#include <fcppt/function/object.hpp>


namespace sgeroids
{
namespace resource_tree
{
template<typename T>
struct path_to_resource_function
{
	typedef
	fcppt::function::object<T const (fcppt::filesystem::path const &)>
	type;
};
}
}

#endif
