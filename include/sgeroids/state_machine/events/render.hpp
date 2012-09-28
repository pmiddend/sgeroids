#ifndef SGEROIDS_STATE_MACHINE_EVENTS_RENDER_HPP_INCLUDED
#define SGEROIDS_STATE_MACHINE_EVENTS_RENDER_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace state_machine
{
namespace events
{
class render
:
	public boost::statechart::event<render>
{
FCPPT_NONASSIGNABLE(
	render);
public:
	explicit
	render(
		sge::renderer::context::ffp &);

	sge::renderer::context::ffp &
	context() const;
private:
	sge::renderer::context::ffp &context_;
};
}
}
}

#endif
