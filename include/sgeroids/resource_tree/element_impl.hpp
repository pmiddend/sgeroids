#ifndef SGEROIDS_RESOURCE_TREE_ELEMENT_IMPL_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_ELEMENT_IMPL_HPP_INCLUDED

#include <sgeroids/resource_tree/element_decl.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/random/make_last_exclusive_range.hpp>

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
		fcppt::random::make_last_exclusive_range(
			static_cast<typename resource_container::size_type>(
				0),
			// Empty elements are allowed, but last_exclusive_range
			// must not be empty, so hack here
			resources_.empty()
			?
				static_cast<typename resource_container::size_type>(
					1)
			:
				resources_.size()),
		_rng)
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
	return
		resources_[
			rng_()].resource();
}

template<typename T>
sgeroids::resource_tree::element<T>::~element()
{
}

#endif
