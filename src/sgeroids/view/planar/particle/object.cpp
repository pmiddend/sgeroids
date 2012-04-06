#include <sgeroids/view/planar/particle/object.hpp>
#include <sgeroids/view/planar/radius.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sgeroids/view/planar/sprite/parameters.hpp>
#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/resource_tree/object_impl.hpp>
#include <sgeroids/resource_tree/path.hpp>
#include <sge/image/colors.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/intrusive/ordered/collection.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/sprite/center.hpp>

sgeroids::view::planar::particle::object::object(
	planar::sprite::ordered_collection &_collection,
	planar::texture_tree &_texture_tree,
	planar::position const &_position,
	particle::velocity const &_velocity,
	particle::lifespan const &_lifespan)
:
	sprite_(
		planar::sprite::parameters()
			.connection(
				_collection.connection(
					3))
			.size(
				planar::sprite_size_from_texture_and_radius(
					*_texture_tree.get(
						sgeroids::resource_tree::path() / FCPPT_TEXT("exhaust")),
					planar::radius(1000 * 1000 * 32)))
			.texture(
				_texture_tree.get(
					sgeroids::resource_tree::path() / FCPPT_TEXT("exhaust")))
			.rotation(
				0)
			.center(
				_position.get())
			.any_color(
				sge::image::colors::white())),
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
	sge::sprite::center(
		sprite_,
		position_);
}

sgeroids::view::planar::particle::object::~object()
{
}
