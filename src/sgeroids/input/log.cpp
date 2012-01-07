#include <sgeroids/input/log.hpp>
#include <sgeroids/log_context.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/parameters/with_context.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sgeroids::input::log()
{
	static fcppt::log::object result(
		fcppt::log::parameters::with_context(
			sgeroids::log_context(),
			fcppt::io::cout(),
			fcppt::log::location(
				FCPPT_TEXT("sgeroids")) / FCPPT_TEXT("input"))
			.level_defaults(
				fcppt::log::level::debug)
			.enabled(
				true));

	return result;
}
