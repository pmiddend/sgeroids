#include <sgeroids/media_path.hpp>
#include <sgeroids/build/media_path.hpp>


fcppt::filesystem::path const
sgeroids::media_path()
{
	return sgeroids::build_media_path();
}
