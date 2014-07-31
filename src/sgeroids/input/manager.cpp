#include <sgeroids/input/keyboard.hpp>
#include <sgeroids/input/log.hpp>
#include <sgeroids/input/manager.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/keyboard/discover_event.hpp>
#include <sge/input/keyboard/remove_event.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/signal/connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sgeroids::input::manager::manager(
	sge::input::processor &_input_processor,
	sgeroids::model::base &_model)
:
	model_(
		_model),
	keyboards_(),
	keyboard_discover_connection_(
		_input_processor.keyboard_discover_callback(
			std::bind(
				&manager::keyboard_discover,
				this,
				std::placeholders::_1))),
	keyboard_remove_connection_(
		_input_processor.keyboard_remove_callback(
			std::bind(
				&manager::keyboard_remove,
				this,
				std::placeholders::_1))),
	last_keyboard_id_(
		0)
{
}

sgeroids::input::manager::~manager()
{
}

void
sgeroids::input::manager::keyboard_discover(
	sge::input::keyboard::discover_event const &e)
{
	sgeroids::model::player_name player_name_id(
		sge::charconv::fcppt_string_to_utf8(
			FCPPT_TEXT("keyboard")+
			fcppt::insert_to_fcppt_string(
				++last_keyboard_id_)));

	FCPPT_LOG_DEBUG(
		input::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Discovered a keyboard! Assigning ID: ")
			<< last_keyboard_id_);

	keyboards_.push_back(
		fcppt::make_unique_ptr<
			input::keyboard
		>(
			model_,
			e.get(),
			player_name_id));
}

void
sgeroids::input::manager::keyboard_remove(
	sge::input::keyboard::remove_event const &e)
{
	FCPPT_LOG_DEBUG(
		input::log(),
		fcppt::log::_ << FCPPT_TEXT("Removed a keyboard!"));

	for(
		keyboard_sequence::iterator it =
			keyboards_.begin();
		it != keyboards_.end();
		++it)
	{
		if(&((*it)->device()) == &(e.get()))
		{
			keyboards_.erase(
				it);
			break;
		}
	}
}
