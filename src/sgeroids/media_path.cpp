#include <sgeroids/media_path.hpp>
#include <sgeroids/build/media_path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


boost::filesystem::path const
sgeroids::media_path()
{
	return sgeroids::build_media_path();
}
