#ifndef SGEROIDS_MODEL_DIM2_HPP_INCLUDED
#define SGEROIDS_MODEL_DIM2_HPP_INCLUDED

#include <fcppt/math/dim/static.hpp>

namespace sgeroids
{
namespace model
{
/**
\brief Represents a dimension in the model

Note that positions and dimensions are <strong>integers</strong> in the model.
See the main documentation page for information about this.
*/
typedef
fcppt::math::dim::static_
<
	int,
	2
>
dim2;
}
}

#endif
