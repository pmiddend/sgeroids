#ifndef SGEROIDS_VIEW_PLANAR_SPRITE_SIZE_FROM_TEXTURE_AND_RADIUS_HPP_INCLUDED
#define SGEROIDS_VIEW_PLANAR_SPRITE_SIZE_FROM_TEXTURE_AND_RADIUS_HPP_INCLUDED

#include <sgeroids/view/planar/radius.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/math/dim/object_impl.hpp>


namespace sgeroids
{
namespace view
{
namespace planar
{
/**
\brief Calculate the 2D size from the radius and the texture (size)

This function is supposed to be called in constructor init lists and thus has
parameters that make this possible in an elegant way. So, instead of taking
just the texture size, it gets the whole texture. And it gets the texture by
<code>_ptr</code> because the texture tree returns this type.
*/
planar::sprite::dim const
sprite_size_from_texture_and_radius(
	sge::texture::part const &,
	planar::radius const &);
}
}
}

#endif
