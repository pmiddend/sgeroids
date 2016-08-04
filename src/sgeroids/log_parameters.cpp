#include <sgeroids/log_parameters.hpp>
#include <fcppt/log/name_fwd.hpp>
#include <fcppt/log/parameters.hpp>
#include <fcppt/log/format/optional_function.hpp>


fcppt::log::parameters
sgeroids::log_parameters(
	fcppt::log::name const &_name
)
{
	return
		fcppt::log::parameters{
			_name,
			fcppt::log::format::optional_function()
		};
}
