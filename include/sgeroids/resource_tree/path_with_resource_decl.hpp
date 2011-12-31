#ifndef SGEROIDS_RESOURCE_TREE_PATH_WITH_RESOURCE_DECL_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_PATH_WITH_RESOURCE_DECL_HPP_INCLUDED

#include <sgeroids/resource_tree/path_with_resource_fwd.hpp>
#include <sgeroids/resource_tree/path.hpp>

namespace sgeroids
{
namespace resource_tree
{
/**
\brief Represents a pair of a path and a resource
*/
template<typename T>
class path_with_resource
{
public:
	explicit
	path_with_resource(
		resource_tree::path const &,
		T);

	resource_tree::path const &
	path() const;

	T const
	resource() const;
private:
	resource_tree::path path_;
	T resource_;
};
}
}

#endif