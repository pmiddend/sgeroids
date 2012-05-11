#ifndef SGEROIDS_STATE_MACHINE_EVENTS_RENDER_HPP_INCLUDED
#define SGEROIDS_STATE_MACHINE_EVENTS_RENDER_HPP_INCLUDED

#include <sge/renderer/context/object_fwd.hpp>
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
		sge::renderer::context::object &);

	sge::renderer::context::object &
	context() const;
private:
	sge::renderer::context::object &context_;
};
}
}
}

#endif
