#ifndef SGEROIDS_STATE_MACHINE_EVENTS_RENDER_HPP_INCLUDED
#define SGEROIDS_STATE_MACHINE_EVENTS_RENDER_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace state_machine
{
namespace events
{
class render
:
	public boost::statechart::event<render>
{
};
}
}
}

#endif
