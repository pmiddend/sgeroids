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
#include <fcppt/optional.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sgeroids
{
namespace input
{
class keyboard
{
FCPPT_NONCOPYABLE(
	keyboard);
public:
	explicit
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
	sgeroids::model::base &model_;
	sge::input::keyboard::device &device_;
	fcppt::signal::scoped_connection key_connection_;
	fcppt::signal::scoped_connection add_spaceship_connection_;
	sgeroids::model::player_name const name_;
	input::optional_entity_id id_;

	void
	key(
		sge::input::keyboard::key_event const &);

	void
	add_spaceship(
		model::entity_id const &,
		model::radius const &,
		model::player_name const &);
};
}
}

#endif
