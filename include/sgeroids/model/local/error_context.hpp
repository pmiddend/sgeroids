#ifndef SGEROIDS_MODEL_LOCAL_ERROR_CONTEXT_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_ERROR_CONTEXT_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sgeroids
{
namespace model
{
namespace local
{
/**
\brief Represents the entity-related function that resulted in an error
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	fcppt::string,
	error_context);
}
}
}

#endif
