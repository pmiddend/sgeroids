#ifndef SGEROIDS_EXCEPTION_HPP_INCLUDED
#define SGEROIDS_EXCEPTION_HPP_INCLUDED

#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>

namespace sgeroids
{
/**
\brief A generic exception type to differentiate sgeroids exceptions from sge/fcppt exceptions
*/
class exception
:
	public fcppt::exception
{
public:
	/**
	\brief Construct an exception with an information string
	\param m Information about the context in which the exception is raised
	*/
	explicit
	exception(
		fcppt::string const &m);

	/**
	\brief Construct an exception from an assertion

	I don't know if this is necessary, really.
	*/
	explicit
	exception(
		fcppt::assert_::information const &);

	virtual
	~exception() throw();
};
}

#endif
