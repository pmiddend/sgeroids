#include <sgeroids/view/planar/object.hpp>

sgeroids::view::planar::object::object(
	sge::renderer::device &,
	sge::font::system &)
{
}

void
sgeroids::view::planar::object::add_spaceship(
	model::entity_id const &,
	model::player_name const &)
{
}

void
sgeroids::view::planar::object::add_asteroid(
	model::entity_id const &,
	model::radius const &)
{
}

void
sgeroids::view::planar::object::add_projectile(
	model::entity_id const &)
{
}

void
sgeroids::view::planar::object::collide_projectile_asteroid(
	model::projectile_id const &,
	model::asteroid_id const &)
{
}

void
sgeroids::view::planar::object::score_change(
	model::score const &)
{
}

void
sgeroids::view::planar::object::destroy_asteroid(
	model::entity_id const &)
{
}

void
sgeroids::view::planar::object::remove_entity(
	model::entity_id const &)
{
}

void
sgeroids::view::planar::object::position_entity(
	model::entity_id const &,
	model::position const &)
{
}

void
sgeroids::view::planar::object::rotation_entity(
	model::entity_id const &,
	model::rotation const &)
{
}

void
sgeroids::view::planar::object::play_area(
	sgeroids::rect const &)
{
}

void
sgeroids::view::planar::object::gameover()
{
}

sgeroids::view::planar::object::~object()
{
}
