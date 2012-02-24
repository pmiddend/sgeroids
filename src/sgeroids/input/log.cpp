#include <sgeroids/log_location.hpp>
#include <sgeroids/log_parameters.hpp>
#include <sgeroids/input/log.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>


namespace
{

fcppt::log::object logger(
	sgeroids::log_parameters(
		sgeroids::log_location() / FCPPT_TEXT("input")));

}

fcppt::log::object &
sgeroids::input::log()
{
	return logger;
}
