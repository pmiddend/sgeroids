#ifndef SGEROIDS_STATES_INGAME_SUPERSTATE_HPP_INCLUDED
#define SGEROIDS_STATES_INGAME_SUPERSTATE_HPP_INCLUDED

namespace sgeroids
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
	public boost::statechart::state<superstate,machine,ingame::running>
{
public:
	explicit
	superstate(
		my_context);

	~superstate();
private:
	sgeroids::view::unique_base_ptr view_;
	sgeroids::model::unique_base_ptr model_;
};
}
}
}

#endif
