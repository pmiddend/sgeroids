#ifndef SGEROIDS_MACHINE_HPP_INCLUDED
#define SGEROIDS_MACHINE_HPP_INCLUDED

#include <sgeroids/states/ingame/superstate_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sgeroids
{
/**
\brief State machine superclass

This class is the game's "parent" class. It contains all systems and variables
that are valid for the whole game duration (the renderer, the config file
etc.).

This machine is initialized in the main.cpp file.
*/
class machine
:
	public boost::statechart::state_machine<machine,states::ingame::superstate>
{
FCPPT_NONCOPYABLE(
	machine);
public:
	explicit
	machine();

	sge::systems::instance const &
	systems() const;

	sge::parse::json::object const &
	config() const;

	~machine();
private:
	sge::systems::instance systems_;
	sge::parse::json::object const config_;
};
}

#endif
