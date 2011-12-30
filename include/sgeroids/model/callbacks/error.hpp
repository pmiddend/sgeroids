#ifndef SGEROIDS_MODEL_CALLBACKS_ERROR_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_ERROR_HPP_INCLUDED

#include <sgeroids/model/callbacks/error_function.hpp>
#include <fcppt/function/object.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function::object<callbacks::error_function>
error;
}
}
}

#endif
