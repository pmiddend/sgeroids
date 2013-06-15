#ifndef SGEROIDS_MODEL_VECTOR2_HPP_INCLUDED
#define SGEROIDS_MODEL_VECTOR2_HPP_INCLUDED

#include <fcppt/math/vector/static.hpp>

namespace sgeroids
{
namespace model
{
/**
\brief Represents a position in the model

Note that positions and dimensions are <strong>integers</strong> in the model.
See the main documentation page for information about this.
*/
typedef
fcppt::math::vector::static_
<
	int,
	2
>
vector2;
}
}

#endif
