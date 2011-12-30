#include <sgeroids/resource_tree/strip_path_prefix.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


sgeroids::resource_tree::path const
sgeroids::resource_tree::strip_path_prefix(
	resource_tree::base_path const &_base_path,
	resource_tree::sub_path const &_sub_path)
{
	sgereoids::resource_tree::path result;
	for(
		fcppt::filesystem::path::const_iterator it =
			boost::next(
				_sub_path.begin(),
				std::distance(
					_base_path.begin(),
					_base_path.end()));
		it != _sub_path.end();
		++it)
		result /=
			fcppt::filesystem::path_to_string(
				it->string());
	return
		result;
}
