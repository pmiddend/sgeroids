#ifndef SGEROIDS_UTF8_FILE_TO_FCPPT_STRING_HPP_INCLUDED
#define SGEROIDS_UTF8_FILE_TO_FCPPT_STRING_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/filesystem/path.hpp>

namespace sgeroids
{
/**
\brief Read a file as UTF-8 and return the contents as fcppt::string
*/
fcppt::string const
utf8_file_to_fcppt_string(
	fcppt::filesystem::path const &);
}

#endif
