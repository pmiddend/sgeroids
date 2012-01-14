#ifndef SGEROIDS_VIEW_PLANAR_CALLBACKS_ADD_PARTICLE_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_CALLBACKS_ADD_PARTICLE_HPP_INCLUDED

#include <sgeroids/view/planar/callbacks/add_particle_function.hpp>
#include <fcppt/function/object.hpp>

namespace sgeroids
{
namespace view
{
namespace planar
{
namespace callbacks
{
typedef
fcppt::function::object<callbacks::add_particle_function>
add_particle;
}
}
}
}

#endif
