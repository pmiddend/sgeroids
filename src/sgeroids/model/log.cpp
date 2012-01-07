#include <sgeroids/log_context.hpp>
#include <sgeroids/model/log.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/parameters/with_context.hpp>


fcppt::log::object &
sgeroids::model::log()
{
	static fcppt::log::object result(
		fcppt::log::parameters::with_context(
			sgeroids::log_context(),
			fcppt::io::cout(),
			fcppt::log::location(
				FCPPT_TEXT("sgeroids")) / FCPPT_TEXT("model"))
			.level_defaults(
				fcppt::log::level::debug)
			.enabled(
				true));

	return result;
}
