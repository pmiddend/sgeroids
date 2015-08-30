#ifndef SGEROIDS_VIEW_UNIQUE_BASE_PTR_HPP_INCLUDED
#define SGEROIDS_VIEW_UNIQUE_BASE_PTR_HPP_INCLUDED

#include <sgeroids/view/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sgeroids
{
namespace view
{
typedef
fcppt::unique_ptr<view::base>
unique_base_ptr;
}
}

#endif
