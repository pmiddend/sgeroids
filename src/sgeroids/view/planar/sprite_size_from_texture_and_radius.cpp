#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sgeroids::view::planar::sprite::dim const
sgeroids::view::planar::sprite_size_from_texture_and_radius(
	sge::texture::const_part_ptr const _texture,
	planar::radius const &_radius)
{
	// Idea: Fix the width to be 2*radius
	// Set the height according to the aspect ratio.

	int const
		texture_width =
			static_cast<int>(
				_texture->size().w()),
		texture_height =
			static_cast<int>(
				_texture->size().h()),
		width =
			2 * _radius.get(),
		height =
			// The aspect ratio is just max(tw,th)/min(tw,th) and
			// we want to calculate w/aspect, so...
			(width * std::min(texture_width,texture_height)) / std::max(texture_width,texture_height);

	return
		sgeroids::view::planar::sprite::dim(
			width,
			height);
}
