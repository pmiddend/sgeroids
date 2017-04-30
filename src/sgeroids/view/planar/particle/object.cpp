#include <sgeroids/view/planar/radius.hpp>
#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/view/planar/texture_tree.hpp>
#include <sgeroids/view/planar/particle/object.hpp>
#include <sgeroids/view/planar/sprite/color_format.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/sprite/intrusive/ordered/collection.hpp>
#include <sge/sprite/roles/center.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <fcppt/text.hpp>


sgeroids::view::planar::particle::object::object(
	planar::sprite::ordered_collection &_collection,
	planar::texture_tree &_texture_tree,
	planar::position const &_position,
	particle::velocity const &_velocity,
	particle::lifespan const &_lifespan)
:
	sprite_(
		sge::sprite::roles::connection{} =
			_collection.connection(
				3
			),
		sge::sprite::roles::size{} =
			planar::sprite_size_from_texture_and_radius(
				*_texture_tree.get(
					sge::resource_tree::path() / FCPPT_TEXT("exhaust")),
				planar::radius(1000 * 1000 * 32)
			),
		sge::sprite::roles::texture0{} =
			sgeroids::view::planar::sprite::object::texture_type{
				_texture_tree.get(
					sge::resource_tree::path() / FCPPT_TEXT("exhaust")
				)
			},
		sge::sprite::roles::rotation{} =
			0.f,
		sge::sprite::roles::center{} =
			_position.get(),
		sge::sprite::roles::color{} =
			sge::image::color::convert<
				sgeroids::view::planar::sprite::color_format
			>(
				sge::image::color::predef::white()
			)
	),
	position_(
		_position.get()),
	velocity_(
		_velocity.get()),
	lifespan_(
		_lifespan),
	dead_(
		false)
{
}

sgeroids::view::planar::particle::object::object(
	object &&
) = default;

sgeroids::view::planar::particle::object &
sgeroids::view::planar::particle::object::operator=(
	object &&
) = default;

bool
sgeroids::view::planar::particle::object::dead()
{
	return dead_;
}

void
sgeroids::view::planar::particle::object::update()
{
	if((lifespan_--).get() <= 0) dead_ = true;
	position_ += velocity_;
	sprite_.center(
		position_);
}

sgeroids::view::planar::particle::object::~object()
{
}
