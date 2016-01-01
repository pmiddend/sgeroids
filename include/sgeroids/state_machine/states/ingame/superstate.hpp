#ifndef SGEROIDS_STATE_MACHINE_STATES_INGAME_SUPERSTATE_HPP_INCLUDED
#define SGEROIDS_STATE_MACHINE_STATES_INGAME_SUPERSTATE_HPP_INCLUDED

#include <sgeroids/input/manager.hpp>
#include <sgeroids/model/unique_base_ptr.hpp>
#include <sgeroids/replay/file_reader_fwd.hpp>
#include <sgeroids/state_machine/object.hpp>
#include <sgeroids/state_machine/events/render.hpp>
#include <sgeroids/state_machine/events/tick.hpp>
#include <sgeroids/view/unique_base_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
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
	boost::filesystem::ofstream model_serialization_output_;
	sgeroids::model::unique_base_ptr model_;
	sgeroids::view::unique_base_ptr view_;

	typedef
	fcppt::optional::object<
		fcppt::unique_ptr<
			sgeroids::input::manager
		>
	>
	optional_input_manager_unique_ptr;

	optional_input_manager_unique_ptr const input_manager_;

	typedef
	fcppt::optional::object<
		fcppt::unique_ptr<
			sgeroids::replay::file_reader
		>
	>
	optional_replay_file_reader_unique_ptr;

	optional_replay_file_reader_unique_ptr const replay_file_reader_;

	fcppt::signal::auto_connection const escape_exit_connection_;

	// Connections from the model to the view
	fcppt::signal::auto_connection const add_spaceship_connection_;
	fcppt::signal::auto_connection const add_asteroid_connection_;
	fcppt::signal::auto_connection const add_projectile_connection_;
	fcppt::signal::auto_connection const collide_projectile_asteroid_connection_;
	fcppt::signal::auto_connection const score_change_connection_;
	fcppt::signal::auto_connection const destroy_asteroid_connection_;
	fcppt::signal::auto_connection const remove_entity_connection_;
	fcppt::signal::auto_connection const position_entity_connection_;
	fcppt::signal::auto_connection const rotation_entity_connection_;
	fcppt::signal::auto_connection const gameover_connection_;
	fcppt::signal::auto_connection const change_thrust_connection_;
};
}
}
}
}

#endif
