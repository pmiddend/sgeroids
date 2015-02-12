#ifndef SGEROIDS_RESOURCE_TREE_INSTANTIATE_OBJECT_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_INSTANTIATE_OBJECT_HPP_INCLUDED

#include <sgeroids/random_generator.hpp>
#include <sge/resource_tree/object_impl.hpp>


#define SGEROIDS_RESOURCE_TREE_INSTANTIATE_OBJECT(\
	type\
)\
template \
class \
sge::resource_tree::object<\
	type, \
	sgeroids::random_generator \
>


#endif
