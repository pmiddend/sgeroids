#ifndef SGEROIDS_REPLAY_DISPATCHER_HPP_INCLUDED
#define SGEROIDS_REPLAY_DISPATCHER_HPP_INCLUDED

#include <sgeroids/model/base_fwd.hpp>
#include <sgeroids/model/serialization/message/base.hpp>
#include <sgeroids/model/serialization/message/add_player.hpp>
#include <sgeroids/model/serialization/message/change_firing_mode.hpp>
#include <sgeroids/model/serialization/message/change_thrust.hpp>
#include <sgeroids/model/serialization/message/rotation_direction.hpp>
#include <sgeroids/model/serialization/message/rng_seed.hpp>
#include <sgeroids/model/serialization/message/update.hpp>
#include <sgeroids/model/serialization/message/remove_player.hpp>
#include <fcppt/noncopyable.hpp>

namespace sgeroids
{
namespace replay
{
class dispatcher
{
FCPPT_NONCOPYABLE(
	dispatcher);
public:
	typedef
	void
	result_type;

	explicit
	dispatcher(
		sgeroids::model::base &);

	result_type
	operator()(
		sgeroids::model::serialization::message::add_player const &) const;

	result_type
	operator()(
		sgeroids::model::serialization::message::change_firing_mode const &) const;

	result_type
	operator()(
		sgeroids::model::serialization::message::change_thrust const &) const;

	result_type
	operator()(
		sgeroids::model::serialization::message::rotation_direction const &) const;

	result_type
	operator()(
		sgeroids::model::serialization::message::rng_seed const &) const;

	result_type
	operator()(
		sgeroids::model::serialization::message::update const &) const;

	result_type
	operator()(
		sgeroids::model::serialization::message::remove_player const &) const;

	~dispatcher();

	void
	default_callback(
		sgeroids::model::serialization::message::base const &);
private:
	sgeroids::model::base &model_;
};
}
}

#endif

