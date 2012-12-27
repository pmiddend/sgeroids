#ifndef SGEROIDS_MODEL_CALLBACKS_ERROR_HPP_INCLUDED
#define SGEROIDS_MODEL_CALLBACKS_ERROR_HPP_INCLUDED

#include <sgeroids/model/callbacks/error_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>

namespace sgeroids
{
namespace model
{
namespace callbacks
{
typedef
std::function<callbacks::error_function>
error;
}
}
}

#endif
