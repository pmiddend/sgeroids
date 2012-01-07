#ifndef SGEROIDS_INPUT_MANAGER_HPP_INCLUDED
#define SGEROIDS_INPUT_MANAGER_HPP_INCLUDED

#include <sgeroids/input/keyboard_fwd.hpp>
#include <sgeroids/model/base_fwd.hpp>
#include <sge/input/keyboard/discover_event_fwd.hpp>
#include <sge/input/keyboard/remove_event_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
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
	explicit
	manager(
		sge::input::processor &,
		sgeroids::model::base &);

	~manager();
private:
	typedef
	boost::ptr_vector<input::keyboard>
	keyboard_sequence;

	sgeroids::model::base &model_;
	keyboard_sequence keyboards_;
	fcppt::signal::scoped_connection keyboard_discover_connection_;
	fcppt::signal::scoped_connection keyboard_remove_connection_;
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
