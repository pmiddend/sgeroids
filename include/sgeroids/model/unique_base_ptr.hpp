#ifndef SGEROIDS_MODEL_UNIQUE_BASE_PTR_HPP_INCLUDED
#define SGEROIDS_MODEL_UNIQUE_BASE_PTR_HPP_INCLUDED

#include <sgeroids/model/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>

namespace sgeroids
{
namespace model
{
typedef
std::unique_ptr<model::base>
unique_base_ptr;
}
}

#endif
