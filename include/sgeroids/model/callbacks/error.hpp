#ifndef SGEROIDS_MODEL_CALLBACKS_ERROR_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_ERROR_HPP_INCLUDED

#include <sgeroids/model/callbacks/error_function.hpp>
#include <fcppt/function_impl.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
fcppt::function<callbacks::error_function>
error;
}
}
}

#endif
