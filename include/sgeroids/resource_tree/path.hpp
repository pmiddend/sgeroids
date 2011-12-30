#ifndef SGEROIDS_RESOURCE_TREE_PATH_HPP_INCLUDED
#define SGEROIDS_RESOURCE_TREE_PATH_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace resource_tree
{
/**
\brief A glorified vector of strings used to locate a resource or group in the tree

The path class has just the operations to work with the tree, it's not a
general-purpose data structure. The user can construct paths "inline" using the
constructor, together with the <code>operator/</code>, like this:

\code
sgeroids::resource_tree::path() / FCPPT_TEXT("foo") / FCPPT_TEXT("bar")
\endcode
*/
class path
{
private:
	typedef
	std::vector<fcppt::string>
	element_sequence;
public:
	typedef
	element_sequence::iterator
	iterator;

	typedef
	element_sequence::const_iterator
	const_iterator;

	explicit
	path();

	path &
	operator/=(
		fcppt::string const &);

	path
	operator/(
		fcppt::string const &) const;

	const_iterator const
	begin() const;

	const_iterator const
	end() const;

	bool
	operator==(
		path const &) const;

	/**
	\brief Return the last element of the path
	*/
	fcppt::string const
	back() const;

	/**
	\brief Output the path as a string for display in error messages
	*/
	fcppt::string const
	string() const;
private:
	element_sequence elements_;
};
}
}

#endif
