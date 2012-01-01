#include <fcppt/tr1/functional.hpp>
#include <sgeroids/model/local/object.hpp>
#include <sgeroids/state_machine/states/ingame/superstate.hpp>
#include <sgeroids/view/planar/object.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <fcppt/text.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/tr1/functional.hpp>


sgeroids::state_machine::states::ingame::superstate::superstate(
	my_context _my_context)
:
	my_base(
		_my_context),
	model_(
		fcppt::make_unique_ptr<sgeroids::model::local::object>()),
	view_(
		fcppt::make_unique_ptr<sgeroids::view::planar::object>(
			fcppt::ref(
				this->context<state_machine::object>().systems().renderer()),
			fcppt::ref(
				this->context<state_machine::object>().systems().font_system()),
			fcppt::ref(
				this->context<state_machine::object>().systems().image_system()),
			fcppt::ref(
				this->context<state_machine::object>().systems().audio_loader()),
			fcppt::ref(
				this->context<state_machine::object>().systems().audio_player()))),
	escape_exit_connection_(
		this->context<state_machine::object>().systems().keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				std::tr1::bind(
					&state_machine::object::exit_mainloop,
					&(this->context<state_machine::object>()))))),
	add_spaceship_connection_(
		model_->add_spaceship_callback(
			std::tr1::bind(
				&view::base::add_spaceship,
				view_.get(),
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				std::tr1::placeholders::_3))),
	add_asteroid_connection_(
		model_->add_asteroid_callback(
			std::tr1::bind(
				&view::base::add_asteroid,
				view_.get(),
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2))),
	add_projectile_connection_(
		model_->add_projectile_callback(
			std::tr1::bind(
				&view::base::add_projectile,
				view_.get(),
				std::tr1::placeholders::_1))),
	collide_projectile_asteroid_connection_(
		model_->collide_projectile_asteroid_callback(
			std::tr1::bind(
				&view::base::collide_projectile_asteroid,
				view_.get(),
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2))),
	score_change_connection_(
		model_->score_change_callback(
			std::tr1::bind(
				&view::base::score_change,
				view_.get(),
				std::tr1::placeholders::_1))),
	destroy_asteroid_connection_(
		model_->destroy_asteroid_callback(
			std::tr1::bind(
				&view::base::destroy_asteroid,
				view_.get(),
				std::tr1::placeholders::_1))),
	remove_entity_connection_(
		model_->remove_entity_callback(
			std::tr1::bind(
				&view::base::remove_entity,
				view_.get(),
				std::tr1::placeholders::_1))),
	position_entity_connection_(
		model_->position_entity_callback(
			std::tr1::bind(
				&view::base::position_entity,
				view_.get(),
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2))),
	gameover_connection_(
		model_->gameover_callback(
			std::tr1::bind(
				&view::base::gameover,
				view_.get())))
{
	view_->play_area(
		model_->play_area());

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
