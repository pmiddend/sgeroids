#ifndef SGEROIDS_MODEL_LOCAL_ENTITY_UNIQUE_BASE_PTR_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_ENTITY_UNIQUE_BASE_PTR_HPP_INCLUDED

#include <sgeroids/model/local/entity/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>

namespace sgeroids
{
namespace model
{
namespace local
{
namespace entity
{
typedef
std::unique_ptr<entity::base>
unique_base_ptr;
}
}
}
}

#endif
