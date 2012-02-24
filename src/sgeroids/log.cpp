#include <sgeroids/log.hpp>
#include <sgeroids/log_location.hpp>
#include <sgeroids/log_parameters.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>


namespace
{

fcppt::log::object logger(
	sgeroids::log_parameters(
		sgeroids::log_location()));

}

fcppt::log::object &
sgeroids::log()
{
	return logger;
}
