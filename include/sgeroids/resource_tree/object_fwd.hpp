#ifndef SGEROIDS_RESOURCE_TREE_OBJECT_FWD_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_OBJECT_FWD_HPP_INCLUDED

#include <sge/resource_tree/object_fwd.hpp>
#include <sgeroids/random_generator_fwd.hpp>


namespace sgeroids
{
namespace resource_tree
{

template<
	typename T
>
struct object
{
	typedef sge::resource_tree::object<
		T,
		sgeroids::random_generator
	> type;
};

}
}

#endif
