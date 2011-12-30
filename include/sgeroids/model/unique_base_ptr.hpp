#ifndef SGEROIDS_MODEL_UNIQUE_BASE_PTR_HPP_INCLUDED
#define SGEROIDS_MODEL_UNIQUE_BASE_PTR_HPP_INCLUDED

#include <sgeroids/model/base_fwd.hpp>
#include <fcppt/unique_ptr.hpp>

namespace sgeroids
{
namespace model
{
typedef
fcppt::unique_ptr<model::base>
unique_base_ptr;
}
}

#endif
