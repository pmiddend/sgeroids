#include <sgeroids/exception.hpp>
#include <fcppt/assert/make_message.hpp>

sgeroids::exception::exception(
	fcppt::string const &_string)
:
	fcppt::exception(
		_string)
{
}

sgeroids::exception::exception(
	fcppt::assert_::information const &_info)
:
	fcppt::exception(
		fcppt::assert_::make_message(
			_info))
{
}

sgeroids::exception::~exception() throw()
{
}
