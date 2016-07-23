#include <sgeroids/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/name.hpp>


fcppt::log::location
sgeroids::log_location()
{
	return
		fcppt::log::location{
			fcppt::log::name{
				FCPPT_TEXT("sgeroids")
			}
		};
}
