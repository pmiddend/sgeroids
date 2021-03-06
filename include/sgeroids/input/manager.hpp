#ifndef SGEROIDS_INPUT_MANAGER_HPP_INCLUDED
#define SGEROIDS_INPUT_MANAGER_HPP_INCLUDED

#include <sgeroids/input/keyboard_fwd.hpp>
#include <sgeroids/model/base_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/keyboard/discover_event_fwd.hpp>
#include <sge/input/keyboard/remove_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/signal/optional_auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace input
{
class manager
{
FCPPT_NONCOPYABLE(
	manager);
public:
	manager(
		fcppt::log::context &,
		sge::input::processor &,
		sgeroids::model::base &);

	~manager();
private:
	typedef
	std::vector<
		fcppt::unique_ptr<
			sgeroids::input::keyboard
		>
	>
	keyboard_sequence;

	fcppt::log::object log_;
	sgeroids::model::base &model_;
	keyboard_sequence keyboards_;
	fcppt::signal::optional_auto_connection const keyboard_discover_connection_;
	fcppt::signal::optional_auto_connection const keyboard_remove_connection_;
	unsigned last_keyboard_id_;

	void
	keyboard_discover(
		sge::input::keyboard::discover_event const &);

	void
	keyboard_remove(
		sge::input::keyboard::remove_event const &);
};
}
}

#endif
