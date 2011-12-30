#ifndef SGEROIDS_STATE_MACHINE_STATES_INGAME_SUPERSTATE_HPP_INCLUDED
#define SGEROIDS_STATE_MACHINE_STATES_INGAME_SUPERSTATE_HPP_INCLUDED

#include <sgeroids/state_machine/events/render.hpp>
#include <sgeroids/state_machine/events/tick.hpp>
#include <sgeroids/state_machine/object.hpp>
#include <sgeroids/model/unique_base_ptr.hpp>
#include <sgeroids/view/unique_base_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/state.hpp>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace state_machine
{
namespace states
{
namespace ingame
{
/**
\brief Contains everything that needs to be accessible during a game
*/
class superstate
:
	public boost::statechart::state<superstate,state_machine::object>
{
public:
	typedef
	boost::mpl::vector2
	<
		boost::statechart::custom_reaction<state_machine::events::tick>,
		boost::statechart::custom_reaction<state_machine::events::render>
	>
	reactions;

	explicit
	superstate(
		my_context);

	boost::statechart::result
	react(
		state_machine::events::tick const &);

	boost::statechart::result
	react(
		state_machine::events::render const &);

	~superstate();
private:
	sgeroids::model::unique_base_ptr model_;
	sgeroids::view::unique_base_ptr view_;
	fcppt::signal::scoped_connection escape_exit_connection_;
};
}
}
}
}

#endif
