#ifndef SGEROIDS_RESOURCE_TREE_OBJECT_IMPL_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_OBJECT_IMPL_HPP_INCLUDED

#include <sgeroids/exception.hpp>
#include <sgeroids/resource_tree/object_decl.hpp>
#include <sgeroids/resource_tree/path_with_resource.hpp>
#include <sgeroids/resource_tree/strip_file_extension.hpp>
#include <sgeroids/resource_tree/strip_path_prefix.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/copy_if.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/is_directory.hpp>
#include <fcppt/filesystem/directory_iterator.hpp>
#include <fcppt/filesystem/is_regular.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/filesystem/recursive_directory_iterator.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <vector>
#include <fcppt/config/external_end.hpp>


template<typename T>
sgeroids::resource_tree::object<T>::object(
	fcppt::filesystem::path const &_path,
	path_to_resource_function const &_path_to_resource,
	sgeroids::random_generator &_random_generator)
{
	FCPPT_ASSERT_PRE(
		fcppt::filesystem::exists(
			_path));

	FCPPT_ASSERT_PRE(
		fcppt::filesystem::is_directory(
			_path));
	typedef
	std::vector<fcppt::filesystem::path>
	path_vector;

	path_vector directories;

	fcppt::algorithm::copy_if(
		fcppt::filesystem::recursive_directory_iterator(
			_path),
		fcppt::filesystem::recursive_directory_iterator(),
		std::back_inserter<path_vector>(
			directories),
		&fcppt::filesystem::is_directory);


	for(
		path_vector::const_iterator it = directories.begin();
		it != directories.end();
		++it)
	{
		path_vector files;

		this->add_directory(
			resource_tree::base_path(
				_path),
			resource_tree::sub_path(
				*it),
			_path_to_resource,
			_random_generator);
	}
}

template<typename T>
void
sgeroids::resource_tree::object<T>::add_directory(
	resource_tree::base_path const &_base_path,
	resource_tree::sub_path const &_sub_path,
	path_to_resource_function const &_path_to_resource,
	sgeroids::random_generator &_random_generator)
{
	typename
	element_type::resource_container
	resources;

	// First, collect ALL the files inside the given directory
	for(
		fcppt::filesystem::directory_iterator it(
			_sub_path.get());
		it != fcppt::filesystem::directory_iterator();
		++it)
	{
		if(!fcppt::filesystem::is_regular(*it))
			continue;

		resources.push_back(
			resource_tree::path_with_resource<T>(
				resource_tree::strip_file_extension(
					resource_tree::strip_path_prefix(
						resource_tree::base_path(
							_sub_path.get()),
						resource_tree::sub_path(
							*it))),
				_path_to_resource(
					*it)));
	}

	// Second, create the element structure containing the files
	fcppt::container::ptr::push_back_unique_ptr(
		elements_,
		fcppt::make_unique_ptr<element_type>(
			resource_tree::strip_path_prefix(
					_base_path,
					_sub_path),
			resources,
			fcppt::ref(
				_random_generator)));
}

template<typename T>
typename
sgeroids::resource_tree::object<T>::value_type
sgeroids::resource_tree::object<T>::get(
	resource_tree::path const &_p)
{
	// Two choices: Either the specified path is a _file_ or a _directory_.
	//
	// If it's a _directory_, we can find it directly. It'll be the
	// base_path member of the element.
	//
	// If it's a _file_, it will be contained inside an element with the
	// according prefix.
	for(
		typename element_sequence::const_iterator it =
			elements_.begin();
		it != elements_.end();
		++it)
	{
		if(it->base_path() == _p)
			return
				it->get_random();

		if(it->contains(_p))
			return it->get(_p);
	}

	throw sgeroids::exception(
		FCPPT_TEXT("Tried to access the location ")+
		_p.string()+
		FCPPT_TEXT(" which could not be found in the resource tree."));
}
template<typename T>
sgeroids::resource_tree::object<T>::~object()
{
}

#endif
