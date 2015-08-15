#include <sgeroids/log_context.hpp>
#include <sgeroids/log_parameters.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location_fwd.hpp>
#include <fcppt/log/parameters.hpp>


fcppt::log::parameters
sgeroids::log_parameters(
	fcppt::log::location const &_location)
{
	return
		fcppt::log::parameters(
			fcppt::io::clog(),
			fcppt::log::level::debug
		).context_location(
			sgeroids::log_context(),
			_location
		)
		.enabled(
			true
		);
}
