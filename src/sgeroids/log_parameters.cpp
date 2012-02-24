#include <sgeroids/log_context.hpp>
#include <sgeroids/log_parameters.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location_fwd.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/parameters/with_context.hpp>


fcppt::log::parameters::object
sgeroids::log_parameters(
	fcppt::log::location const &_location)
{
	return
		fcppt::log::parameters::with_context(
			sgeroids::log_context(),
			_location)
		.level_defaults(
			fcppt::io::clog(),
			fcppt::log::level::debug)
		.enabled(
			true);

}
