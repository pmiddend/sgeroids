#include <sgeroids/state_machine/object.hpp>
#include <sgeroids/state_machine/states/ingame/superstate.hpp>
#include <sgeroids/version.hpp>
#include <fcppt/scoped_state_machine.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int
main(
	int const argc,
	char *argv[])
try
{
	fcppt::io::cerr() << sgeroids::version() << FCPPT_TEXT("\n");
	sgeroids::state_machine::object m(
		argc,
		argv);

	fcppt::scoped_state_machine<sgeroids::state_machine::object> sm(
		m);

	m.run();
}
catch(
	fcppt::exception const &e)
{
	fcppt::io::cerr()
		<< FCPPT_TEXT("fcppt::exception: ")
		<< e.string()
		<< FCPPT_TEXT("\n");
	return EXIT_FAILURE;
}
catch(
	std::exception const &e)
{
	std::cerr
		<< "std::exception: "
		<< e.what()
		<< "\n";

	return EXIT_FAILURE;
}
