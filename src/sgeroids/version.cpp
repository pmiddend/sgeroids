#include <sgeroids/version.hpp>
#include <sgeroids/build/version.hpp>


fcppt::string const
sgeroids::version()
{
	return sgeroids::build_version();
}
