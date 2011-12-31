#include <sgeroids/resource_tree/strip_file_extension.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <boost/spirit/home/phoenix/core.hpp>
#include <boost/spirit/home/phoenix/operator.hpp>
#include <functional>
#include <numeric>
#include <fcppt/config/external_end.hpp>


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
			boost::phoenix::arg_names::arg1 / boost::phoenix::arg_names::arg2) /
		filename.substr(0,dot_position);
}
