#ifndef SGEROIDS_EXCEPTION_HPP_INCLUDED
#define SGEROIDS_EXCEPTION_HPP_INCLUDED

#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>

namespace sgeroids
{
class exception
:
	public fcppt::exception
{
public:
	explicit
	exception(
		fcppt::string const &);

	explicit
	exception(
		fcppt::assert_::information const &);

	virtual
	~exception() throw();
};
}

#endif
