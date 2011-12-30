#include <sgeroids/view/log.hpp>

fcppt::log::object &
sgeroids::view::log()
{
	static fcppt::log::object result(
		fcppt::log::parameters::with_context(
			sgeroids::log_context(),
			fcppt::io::cout(),
			fcppt::log::location(
				FCPPT_TEXT("sgeroids")) / FCPPT_TEXT("view"))
			.level_defaults(
				fcppt::log::level::debug)
			.enabled(
				true));

	return result;
}
