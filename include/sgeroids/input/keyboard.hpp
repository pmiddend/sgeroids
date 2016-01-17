#ifndef SGEROIDS_INPUT_KEYBOARD_HPP_INCLUDED
#define SGEROIDS_INPUT_KEYBOARD_HPP_INCLUDED

#include <sgeroids/input/optional_entity_id.hpp>
#include <sgeroids/model/base_fwd.hpp>
#include <sgeroids/model/entity_id.hpp>
#include <sgeroids/model/player_name.hpp>
#include <sgeroids/model/radius.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sgeroids
{
namespace input
{
class keyboard
{
FCPPT_NONCOPYABLE(
	keyboard);
public:
	keyboard(
		sgeroids::model::base &,
		sge::input::keyboard::device &,
		sgeroids::model::player_name const &);

	sge::input::keyboard::device &
	device() const;

	sgeroids::model::player_name const &
	name() const;

	input::optional_entity_id const &
	id() const;

	~keyboard();
private:
	fcppt::reference<
		sgeroids::model::base
	> model_;

	fcppt::reference<
		sge::input::keyboard::device
	> device_;
	fcppt::signal::auto_connection const key_connection_;
	fcppt::signal::auto_connection const add_spaceship_connection_;
	fcppt::signal::auto_connection const remove_spaceship_connection_;
	sgeroids::model::player_name name_;
	sgeroids::input::optional_entity_id id_;
	bool rotation_left_pressed_,rotation_right_pressed_;

	void
	key(
		sge::input::keyboard::key_event const &);

	void
	key_impl(
		sge::input::keyboard::key_event const &,
		sgeroids::model::entity_id
	);

	void
	add_spaceship(
		model::entity_id const &,
		model::radius const &,
		model::player_name const &);

	void
	remove_spaceship(
		model::player_name const &);
};
}
}

#endif
