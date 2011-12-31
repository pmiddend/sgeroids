#ifndef SGEROIDS_MEDIA_PATH_HPP_INCLUDED
#define SGEROIDS_MEDIA_PATH_HPP_INCLUDED

#include <fcppt/filesystem/path.hpp>

namespace sgeroids
{
/**
\brief Return the path to the media directory

To see how this media path stuff works, check the main documentation
*/
fcppt::filesystem::path const
media_path();
}

#endif
