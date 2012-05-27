#include <sgeroids/input/keyboard.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sgeroids/input/log.hpp>
#include <sgeroids/input/manager.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/keyboard/discover_event.hpp>
#include <sge/input/keyboard/remove_event.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/signal/connection.hpp>
#include <fcppt/tr1/functional.hpp>


sgeroids::input::manager::manager(
	sge::input::processor &_input_processor,
	sgeroids::model::base &_model,
	sge::charconv::system &_charconv_system)
:
	model_(
		_model),
	charconv_system_(
		_charconv_system),
	keyboards_(),
	keyboard_discover_connection_(
		_input_processor.keyboard_discover_callback(
			std::tr1::bind(
				&manager::keyboard_discover,
				this,
				std::tr1::placeholders::_1))),
	keyboard_remove_connection_(
		_input_processor.keyboard_remove_callback(
			std::tr1::bind(
				&manager::keyboard_remove,
				this,
				std::tr1::placeholders::_1))),
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
			charconv_system_,
			FCPPT_TEXT("keyboard")+
			fcppt::insert_to_fcppt_string(
				++last_keyboard_id_)));

	FCPPT_LOG_DEBUG(
		input::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Discovered a keyboard! Assigning ID: ")
			<< last_keyboard_id_);

	fcppt::container::ptr::push_back_unique_ptr(
		keyboards_,
		fcppt::make_unique_ptr<input::keyboard>(
			fcppt::ref(
				model_),
			fcppt::ref(
				e.get()),
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
		if(&(it->device()) == &(e.get()))
		{
			keyboards_.erase(
				it);
			break;
		}
	}
}
