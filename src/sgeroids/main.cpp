#include <sgeroids/main.hpp>
#include <sgeroids/version.hpp>
#include <sgeroids/state_machine/object.hpp>
#include <sgeroids/state_machine/states/ingame/superstate.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/scoped_state_machine.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
sgeroids::main(
	awl::main::function_context const &_main_function_context)
try
{
	sgeroids::state_machine::object machine(
		_main_function_context.argc(),
		_main_function_context.argv());

	fcppt::scoped_state_machine<sgeroids::state_machine::object> const scoped_machine(
		machine);

	return
		machine.run();
}
catch(
	fcppt::exception const &e)
{
	fcppt::io::cerr()
		<< FCPPT_TEXT("fcppt::exception: ")
		<< e.string()
		<< FCPPT_TEXT("\n");
	return awl::main::exit_failure();
}
catch(
	std::exception const &e)
{
	std::cerr
		<< "std::exception: "
		<< e.what()
		<< "\n";

	return awl::main::exit_failure();
}
