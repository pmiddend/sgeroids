#ifndef SGEROIDS_MEDIA_PATH_HPP_INCLUDED
#define SGEROIDS_MEDIA_PATH_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

namespace sgeroids
{
/**
\brief Return the path to the media directory

To see how this media path stuff works, check the main documentation
*/
boost::filesystem::path const
media_path();
}

#endif
