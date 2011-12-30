#include <sgeroids/resource_tree/strip_file_extension.hpp>
#include <fcppt/text.hpp>
#include <boost/next_prior.hpp>
#include <algorithm>
#include <functional>

sgeroids::resource_tree::path const
sgeroids::resource_tree::strip_file_extension(
	resource_tree::path const &p)
{
	fcppt::string const filename =
		p.back();

	fcppt::string::size_type const dot_position =
		filename.find(
			FCPPT_TEXT('.'));

	if(dot_position == fcppt::string::npos)
		return p;

	return
		std::accumulate(
			p.begin(),
			boost::prior(
				p.end()),
			resource_tree::path(),
			std::divides<resource_tree::path>()) /
		filename.substr(0,dot_position);
}
