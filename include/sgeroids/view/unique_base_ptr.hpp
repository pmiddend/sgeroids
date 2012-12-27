#ifndef SGEROIDS_VIEW_UNIQUE_BASE_PTR_HPP_INCLUDED
#define SGEROIDS_VIEW_UNIQUE_BASE_PTR_HPP_INCLUDED

#include <sgeroids/view/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>

namespace sgeroids
{
namespace view
{
typedef
std::unique_ptr<view::base>
unique_base_ptr;
}
}

#endif
