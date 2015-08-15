#ifndef SGEROIDS_MODEL_LOCAL_CALLBACKS_INCREASE_SCORE_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_CALLBACKS_INCREASE_SCORE_HPP_INCLUDED

#include <sgeroids/model/local/callbacks/increase_score_function.hpp>
#include <fcppt/function_impl.hpp>

namespace sgeroids
{
namespace model
{
namespace local
{
namespace callbacks
{
typedef
fcppt::function<local::callbacks::increase_score_function>
increase_score;
}
}
}
}

#endif

