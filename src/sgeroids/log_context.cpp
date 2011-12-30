#include <sgeroids/log_context.hpp>
#include <fcppt/log/context.hpp>

fcppt::log::context &
sgeroids::log_context()
{
	static fcppt::log::context result;
	return result;
}
