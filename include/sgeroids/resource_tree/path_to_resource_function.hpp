#ifndef SGEROIDS_RESOURCE_TREE_PATH_TO_RESOURCE_FUNCTION_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_PATH_TO_RESOURCE_FUNCTION_HPP_INCLUDED

#include <fcppt/function/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace resource_tree
{
template<typename T>
struct path_to_resource_function
{
	typedef
	fcppt::function::object<T const (boost::filesystem::path const &)>
	type;
};
}
}

#endif
