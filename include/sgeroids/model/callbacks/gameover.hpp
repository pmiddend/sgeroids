#ifndef SGEROIDS_MODEL_CALLBACKS_GAMEOVER_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_GAMEOVER_HPP_INCLUDED

#include <sgeroids/model/callbacks/gameover_function.hpp>
#include <fcppt/function_impl.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function<callbacks::gameover_function>
gameover;
}
}
}

#endif
