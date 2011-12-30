#include <sgeroids/log_context.hpp>
#include <sgeroids/log.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/parameters/root.hpp>
#include <fcppt/io/cout.hpp>

fcppt::log::object &
sgeroids::log()
{
	static fcppt::log::object result(
		fcppt::log::parameters::with_context(
			sgeroids::log_context(),
			fcppt::io::cout(),
			fcppt::log::location(
				FCPPT_TEXT("sgeroids")))
			.level_defaults(
				fcppt::log::level::debug)
			.enabled(
				true));

	return result;
}
