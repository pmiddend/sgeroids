#include <sgeroids/state_machine/events/render.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


sgeroids::state_machine::events::render::render(
	sge::renderer::context::ffp &_context)
:
	context_(
		_context)
{
}

sge::renderer::context::ffp &
sgeroids::state_machine::events::render::context() const
{
	return
		context_;
}
