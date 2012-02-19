#ifndef SGEROIDS_STATE_MACHINE_OBJECT_HPP_INCLUDED
#define SGEROIDS_STATE_MACHINE_OBJECT_HPP_INCLUDED

#include <sgeroids/state_machine/states/ingame/superstate_fwd.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/systems/instance.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/state_machine.hpp>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace state_machine
{
/**
\brief State machine superclass

This class is the game's "parent" class. It contains all systems and variables
that are valid for the whole game duration (the renderer, the config file
etc.).

This machine is initialized in the main.cpp file.
*/
class object
:
	public boost::statechart::state_machine<object,states::ingame::superstate>
{
FCPPT_NONCOPYABLE(
	object);
public:
	explicit
	object(
		int,
		char*[]);

	sge::parse::json::object const &
	config() const;

	sge::systems::instance const &
	systems() const;

	awl::main::exit_code const
	run();

	void
	exit_mainloop();

	~object();
private:
	sge::parse::json::object const config_;
	sge::systems::instance systems_;
};
}
}

#endif
