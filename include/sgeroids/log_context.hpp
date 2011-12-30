#ifndef SGEROIDS_LOG_CONTEXT_HPP_INCLUDED
#define SGEROIDS_LOG_CONTEXT_HPP_INCLUDED

#include <fcppt/log/context_fwd.hpp>

namespace sgeroids
{
/**
\brief Return the global log context singleton which is used by all the loggers
*/
fcppt::log::context &
log_context();
}

#endif
