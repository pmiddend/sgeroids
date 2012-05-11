#include <sgeroids/state_machine/events/render.hpp>
#include <sge/renderer/context/object_fwd.hpp>


sgeroids::state_machine::events::render::render(
	sge::renderer::context::object &_context)
:
	context_(
		_context)
{
}

sge::renderer::context::object &
sgeroids::state_machine::events::render::context() const
{
	return
		context_;
}
