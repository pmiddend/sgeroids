#ifndef SGEROIDS_REPLAY_OBJECT_HPP_INCLUDED
#define SGEROIDS_REPLAY_OBJECT_HPP_INCLUDED

#include <sgeroids/model/base_fwd.hpp>
#include <sgeroids/replay/call_object.hpp>
#include <sgeroids/replay/dispatcher.hpp>
#include <alda/call/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace replay
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	object(
		sgeroids::model::base &,
		std::istream &);

	void
	update();

	bool
	done() const;

	~object();
private:
	FCPPT_MAKE_STRONG_TYPEDEF(
		bool,
		was_update_message);

	std::istream &input_stream_;
	sgeroids::replay::call_object call_object_;
	sgeroids::replay::dispatcher dispatcher_;

	was_update_message const
	deserialize_single_message();
};
}
}

#endif

