#include <sgeroids/model/local/object.hpp>
#include <sgeroids/state_machine/states/ingame/superstate.hpp>
#include <sgeroids/view/planar/object.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <fcppt/text.hpp>
#include <fcppt/tr1/functional.hpp>


sgeroids::state_machine::states::ingame::superstate::superstate(
	my_context my_context)
:
	my_base(
		my_context),
	model_(
		fcppt::make_unique_ptr<sgeroids::model::local::object>())
	view_(
		fcppt::make_unique_ptr<sgeroids::view::planar::object>(
			this->context<state_machine::object>().systems().renderer(),
			this->context<state_machine::object>().systems().font_system(),
			this->context<state_machine::object>().systems().image_system(),
			this->context<state_machine::object>().systems().audio_loader(),
			this->context<state_machine::object>().systems().audio_player())),
	escape_exit_connection_(
		this->context<state_machine::object>.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				std::tr1::bind(
					&state_machine::object::exit_mainloop,
					&(this->context<state_machine::object>)))))
{
	model_->add_player(
		model::player_name(
			FCPPT_TEXT("Spast")));
}

boost::statechart::result
sgeroids::state_machine::states::ingame::superstate::react(
	state_machine::events::tick const &)
{
	model_->update();
	view_->update();
	return discard_event();
}

boost::statechart::result
sgeroids::state_machine::states::ingame::superstate::react(
	state_machine::events::render const &)
{
	view_->render();
	return discard_event();
}

sgeroids::state_machine::states::ingame::superstate::~superstate()
{
}
