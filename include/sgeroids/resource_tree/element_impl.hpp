#ifndef SGEROIDS_RESOURCE_TREE_ELEMENT_IMPL_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_ELEMENT_IMPL_HPP_INCLUDED

#include <sgeroids/random_generator.hpp>
#include <sgeroids/resource_tree/element_decl.hpp>
#include <sgeroids/resource_tree/path.hpp>
#include <sgeroids/resource_tree/path_with_resource.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/uniform_int_impl.hpp>

template<typename T>
sgeroids::resource_tree::element<T>::element(
	resource_tree::path const &_base_path,
	resource_container const &_resources,
	sgeroids::random_generator &_rng)
:
	base_path_(
		_base_path),
	resources_(
		_resources),
	rng_(
		_rng,
		container_distribution(
			typename container_distribution::min(
				0u),
			// Empty resource containers are allowed.
			// In this case, rng_ should not be used.
			typename container_distribution::max(
				resources_.empty()
				?
					0u
				:
					resources_.size() - 1u)))
{
}

template<typename T>
sgeroids::resource_tree::path const &
sgeroids::resource_tree::element<T>::base_path() const
{
	return
		base_path_;
}

template<typename T>
bool
sgeroids::resource_tree::element<T>::contains(
	resource_tree::path const &s) const
{
	for(
		typename resource_container::const_iterator it =
			resources_.begin();
		it != resources_.end();
		++it)
		if(base_path_ / it->path().string() == s)
			return true;
	return false;
}

template<typename T>
T
sgeroids::resource_tree::element<T>::get(
	resource_tree::path const &s) const
{
	FCPPT_ASSERT_PRE(
		this->contains(
			s));

	for(
		typename resource_container::const_iterator it =
			resources_.begin();
		it != resources_.end();
		++it)
		if(base_path_ / it->path().string() == s)
			return it->resource();

	FCPPT_ASSERT_UNREACHABLE;
}

template<typename T>
T
sgeroids::resource_tree::element<T>::get_random() const
{
	FCPPT_ASSERT_PRE(
		!resources_.empty());

	return
		resources_[
			rng_()].resource();
}

template<typename T>
sgeroids::resource_tree::element<T>::~element()
{
}

#endif
