#ifndef SGEROIDS_RESOURCE_TREE_PATH_WITH_RESOURCE_IMPL_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_PATH_WITH_RESOURCE_IMPL_HPP_INCLUDED

template<typename T>
sgeroids::resource_tree::path_with_resource<T>::path_with_resource(
	resource_tree::path const &_path,
	T const _resource)
:
	path_(
		_path),
	resource_(
		_resource)
{
}

template<typename T>
sgeroids::resource_tree::path const &
sgeroids::resource_tree::path_with_resource<T>::path() const
{
	return path_;
}

template<typename T>
T const
sgeroids::resource_tree::path_with_resource<T>::resource() const
{
	return resource_;
}

#endif
