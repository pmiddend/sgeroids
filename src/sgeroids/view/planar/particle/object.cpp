#include <sgeroids/view/planar/particle/object.hpp>
#include <sgeroids/view/planar/radius.hpp>
#include <sgeroids/view/planar/sprite/dim.hpp>
#include <sgeroids/view/planar/sprite/parameters.hpp>
#include <sgeroids/view/planar/sprite/system_impl.hpp>
#include <sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp>
#include <sgeroids/resource_tree/object_impl.hpp>
#include <sgeroids/resource_tree/path.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/any/object.hpp>

sgeroids::view::planar::particle::object::object(
	planar::sprite::system &_sprite_system,
	planar::texture_tree &_texture_tree,
	planar::position const &_position,
	particle::velocity const &_velocity,
	particle::lifespan const &_lifespan)
:
	sprite_(
		planar::sprite::parameters()
			.system(
				_sprite_system)
			.size(
				planar::sprite_size_from_texture_and_radius(
					_texture_tree.get(
						sgeroids::resource_tree::path() / FCPPT_TEXT("exhaust")),
					planar::radius(1000 * 1000 * 32)))
			.texture(
				_texture_tree.get(
					sgeroids::resource_tree::path() / FCPPT_TEXT("exhaust")))
			.order(
				3)
			.rotation(
				0)
			.pos(
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
	if(lifespan_.get()-- <= 0) dead_ = true;
	position_ += velocity_;
	sprite_.pos(
		position_);
}

sgeroids::view::planar::particle::object::~object()
{
}
