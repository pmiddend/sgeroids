#ifndef SGEROIDS_RESOURCE_TREE_ELEMENT_DECL_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_ELEMENT_DECL_HPP_INCLUDED

#include <sgeroids/random_generator_fwd.hpp>
#include <sgeroids/resource_tree/element_fwd.hpp>
#include <sgeroids/resource_tree/path.hpp>
#include <sgeroids/resource_tree/path_with_resource.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/random/variate_decl.hpp>
#include <fcppt/random/distribution/uniform_int_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace resource_tree
{
/**
\brief Represents one directory with the immediately contained resources (no recursion)

An element is a container for resources along with their paths. When the tree
is asked to return a resource (designated by a path, of course), it...

<ul>
	<li>
		...iterates through its elements and checks if the current element's
		\link sgeroids::resource_tree::element::base_path base_path
		\endlink is equal to the specified path or not.
	</li>
	<li>
		If it's equal, it calls sgeroids::resource_tree::element::get_random to
		get a random element.
	</li>
	<li>
		If it's not equal, check if the element contains the path using
		sgeroids::resource_tree::element::contains. If it doesn't
		proceed to the next element. If it does contain the path,
		return the resource attached to it using
		sgeroids::resource_tree::element::get.
	</li>
</ul>
*/
template<typename T>
class element
{
FCPPT_NONCOPYABLE(
	element);
public:
	typedef
	std::vector
	<
		resource_tree::path_with_resource<T>
	>
	resource_container;

	explicit
	element(
		resource_tree::path const &,
		resource_container const &,
		sgeroids::random_generator &);

	resource_tree::path const &
	base_path() const;

	bool
	contains(
		resource_tree::path const &) const;

	T
	get(
		resource_tree::path const &) const;

	T
	get_random() const;

	~element();
private:
	resource_tree::path const base_path_;
	resource_container resources_;
	typedef fcppt::random::distribution::uniform_int<
		typename resource_container::size_type
	> container_distribution;
	mutable fcppt::random::variate<sgeroids::random_generator, container_distribution> rng_;
};
}
}

#endif
