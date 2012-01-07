#include <sgeroids/resource_tree/path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sgeroids::resource_tree::path::path()
:
	elements_()
{
}

sgeroids::resource_tree::path &
sgeroids::resource_tree::path::operator/=(
	fcppt::string const &s)
{
	elements_.push_back(
		s);
	return *this;
}

sgeroids::resource_tree::path
sgeroids::resource_tree::path::operator/(
	fcppt::string const &s) const
{
	path result(
		*this);

	result /= s;

	return result;
}

sgeroids::resource_tree::path::const_iterator const
sgeroids::resource_tree::path::begin() const
{
	return elements_.begin();
}

sgeroids::resource_tree::path::const_iterator const
sgeroids::resource_tree::path::end() const
{
	return elements_.end();
}

bool
sgeroids::resource_tree::path::operator==(
	path const &_p) const
{
	return
		elements_.size() == _p.elements_.size() &&
		std::equal(
			elements_.begin(),
			elements_.end(),
			_p.elements_.begin());
}

fcppt::string const
sgeroids::resource_tree::path::back() const
{
	return elements_.back();
}

fcppt::string const
sgeroids::resource_tree::path::string() const
{
	fcppt::string result;

	for(
		element_sequence::const_iterator it =
			elements_.begin();
		it != elements_.end();
		++it)
	{
		if(it != boost::prior(elements_.end()))
			result += (*it)+FCPPT_TEXT("/");
		else
			result += (*it);
	}

	return result;
}
