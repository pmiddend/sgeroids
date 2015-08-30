#include <sgeroids/model/local/object.hpp>
#include <sgeroids/replay/file_reader.hpp>
#include <sgeroids/state_machine/states/ingame/superstate.hpp>
#include <sgeroids/view/planar/object.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <memory>
#include <fcppt/config/external_end.hpp>


sgeroids::state_machine::states::ingame::superstate::superstate(
	my_context _my_context)
:
	my_base(
		_my_context),
	model_serialization_output_(
		boost::filesystem::path(
			sge::parse::json::find_and_convert_member<fcppt::string>(
				this->context<state_machine::object>().config(),
				sge::parse::json::path(
					FCPPT_TEXT("serialization")) /
					FCPPT_TEXT("output-file")))),
	model_(
		fcppt::unique_ptr_to_base<
			sgeroids::model::base
		>(
			fcppt::make_unique_ptr_fcppt<
				sgeroids::model::local::object
			>(
				model_serialization_output_
			)
		)
	),
	view_(
		fcppt::unique_ptr_to_base<
			sgeroids::view::base
		>(
			fcppt::make_unique_ptr_fcppt<
				sgeroids::view::planar::object
			>(
				this->context<state_machine::object>().systems().renderer_device_ffp(),
				this->context<state_machine::object>().systems().font_system(),
				this->context<state_machine::object>().systems().image_system(),
				this->context<state_machine::object>().systems().audio_loader(),
				this->context<state_machine::object>().systems().audio_player()
			)
		)
	),
	input_manager_(
		sge::parse::json::find_and_convert_member<fcppt::string>(
			this->context<state_machine::object>().config(),
			sge::parse::json::path(
				FCPPT_TEXT("serialization")
			)
			/
			FCPPT_TEXT("input-file")
		).empty()
		?
			optional_input_manager_unique_ptr(
				fcppt::make_unique_ptr_fcppt<
					sgeroids::input::manager
				>(
					this->context<state_machine::object>().systems().input_processor(),
					*model_
				)
			)
		:
			optional_input_manager_unique_ptr()
	),
	replay_file_reader_(
		sge::parse::json::find_and_convert_member<fcppt::string>(
			this->context<state_machine::object>().config(),
			sge::parse::json::path(
				FCPPT_TEXT("serialization")) /
				FCPPT_TEXT("input-file")).empty()
		?
			optional_replay_file_reader_unique_ptr()
		:
			optional_replay_file_reader_unique_ptr(
				fcppt::make_unique_ptr_fcppt<sgeroids::replay::file_reader>(
					*model_,
					boost::filesystem::path(
						sge::parse::json::find_and_convert_member<fcppt::string>(
							this->context<state_machine::object>().config(),
							sge::parse::json::path(
								FCPPT_TEXT("serialization")
							)
							/
							FCPPT_TEXT("input-file")
						)
					)
				)
			)
	),
	escape_exit_connection_(
		this->context<state_machine::object>().systems().keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::input::keyboard::action_callback{
					std::bind(
						&state_machine::object::exit_mainloop,
						&(this->context<state_machine::object>())
					)
				}
			)
		)
	),
	add_spaceship_connection_(
		model_->add_spaceship_callback(
			sgeroids::model::callbacks::add_spaceship{
				std::bind(
					&view::base::add_spaceship,
					view_.get_pointer(),
					std::placeholders::_1,
					std::placeholders::_2,
					std::placeholders::_3
				)
			}
		)
	),
	add_asteroid_connection_(
		model_->add_asteroid_callback(
			sgeroids::model::callbacks::add_asteroid{
				std::bind(
					&view::base::add_asteroid,
					view_.get_pointer(),
					std::placeholders::_1,
					std::placeholders::_2
				)
			}
		)
	),
	add_projectile_connection_(
		model_->add_projectile_callback(
			sgeroids::model::callbacks::add_projectile{
				std::bind(
					&view::base::add_projectile,
					view_.get_pointer(),
					std::placeholders::_1
				)
			}
		)
	),
	collide_projectile_asteroid_connection_(
		model_->collide_projectile_asteroid_callback(
			sgeroids::model::callbacks::collide_projectile_asteroid{
				std::bind(
					&view::base::collide_projectile_asteroid,
					view_.get_pointer(),
					std::placeholders::_1,
					std::placeholders::_2
				)
			}
		)
	),
	score_change_connection_(
		model_->score_change_callback(
			sgeroids::model::callbacks::score_change{
				std::bind(
					&view::base::score_change,
					view_.get_pointer(),
					std::placeholders::_1,
					std::placeholders::_2
				)
			}
		)
	),
	destroy_asteroid_connection_(
		model_->destroy_asteroid_callback(
			sgeroids::model::callbacks::destroy_asteroid{
				std::bind(
					&view::base::destroy_asteroid,
					view_.get_pointer(),
					std::placeholders::_1
				)
			}
		)
	),
	remove_entity_connection_(
		model_->remove_entity_callback(
			sgeroids::model::callbacks::remove_entity{
				std::bind(
					&view::base::remove_entity,
					view_.get_pointer(),
					std::placeholders::_1
				)
			}
		)
	),
	position_entity_connection_(
		model_->position_entity_callback(
			sgeroids::model::callbacks::position_entity{
				std::bind(
					&view::base::position_entity,
					view_.get_pointer(),
					std::placeholders::_1,
					std::placeholders::_2
				)
			}
		)
	),
	rotation_entity_connection_(
		model_->rotation_entity_callback(
			sgeroids::model::callbacks::rotation_entity{
				std::bind(
					&view::base::rotation_entity,
					view_.get_pointer(),
					std::placeholders::_1,
					std::placeholders::_2
				)
			}
		)
	),
	gameover_connection_(
		model_->gameover_callback(
			sgeroids::model::callbacks::gameover{
				std::bind(
					&view::base::gameover,
					view_.get_pointer()
				)
			}
		)
	),
	change_thrust_connection_(
		model_->change_thrust_callback(
			sgeroids::model::callbacks::change_thrust{
				std::bind(
					&view::base::change_thrust,
					view_.get_pointer(),
					std::placeholders::_1,
					std::placeholders::_2
				)
			}
		)
	)
{
	view_->play_area(
		model_->play_area());

	if(
		!replay_file_reader_.has_value()
	)
		model_->process_message(
			sgeroids::model::serialization::message::rng_seed(
				sgeroids::model::serialization::message::roles::seed{} =
					fcppt::random::generator::seed_from_chrono<sgeroids::random_generator::seed>().get()));
}

boost::statechart::result
sgeroids::state_machine::states::ingame::superstate::react(
	state_machine::events::tick const &)
{
	fcppt::maybe_void(
		replay_file_reader_,
		[](
			auto const &_replay
		)
		{
			_replay->update();
		}
	);

	model_->process_message(
		sgeroids::model::serialization::message::update());

	view_->update();

	return
		discard_event();
}

boost::statechart::result
sgeroids::state_machine::states::ingame::superstate::react(
	state_machine::events::render const &_event)
{
	view_->render(
		_event.context());
	return discard_event();
}

sgeroids::state_machine::states::ingame::superstate::~superstate()
{
}
