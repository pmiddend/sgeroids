#include <sgeroids/log_location.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/text.hpp>

fcppt::log::location const
sgeroids::log_location()
{
	return
		fcppt::log::location(
			FCPPT_TEXT("sgeroids"));
}