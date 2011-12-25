#include <sgeroids/model/local/object.hpp>

sgeroids::model::local::object::object()
:
	entities_(),
	next_id_(
		0u)
{
}

void
sgeroids::model::local::object::update()
{
	this->entity_updates();
	this->collision_detection();
}

fcppt::signal::auto_connection
sgeroids::model::local::object::add_spaceship_callback(
	callbacks::add_spaceship const &)
{
}

fcppt::signal::auto_connection
sgeroids::model::local::object::add_asteroid_callback(
	callbacks::add_asteroid const &)
{
}

fcppt::signal::auto_connection
sgeroids::model::local::object::add_projectile_callback(
	callbacks::add_projectile const &)
{
}

fcppt::signal::auto_connection
sgeroids::model::local::object::collide_projectile_asteroid_callback(
	callbacks::collide_projectile_asteroid const &)
{
}

fcppt::signal::auto_connection
sgeroids::model::local::object::score_change_callback(
	callbacks::score_change const &)
{
}

fcppt::signal::auto_connection
sgeroids::model::local::object::destroy_asteroid_callback(
	callbacks::destroy_asteroid const &)
{
}

fcppt::signal::auto_connection
sgeroids::model::local::object::remove_entity_callback(
	callbacks::remove_entity const &)
{
}

fcppt::signal::auto_connection
sgeroids::model::local::object::position_entity_callback(
	callbacks::entity_position const &)
{
}

fcppt::signal::auto_connection
sgeroids::model::local::object::rotation_entity_callback(
	callbacks::entity_rotation const &)
{
}

fcppt::signal::auto_connection
sgeroids::model::local::object::gameover_callback(
	callbacks::gameover const &)
{
}

void
sgeroids::model::local::object::add_player(
	model::player_name const &_player_name)
{
	// First, search for a player with the given name. If one already
	// exists, we have to signal an error.
	for(
		entity_map::const_iterator it =
			entities_.begin();
		it != entities_.end();
		++it)
	{
		fcppt::optional<entity::spaceship &> maybe_a_ship(
			fcppt::optional_dynamic_cast<entity::spaceship &>(
				*(it->second)));

		if(!maybe_a_ship)
			continue;

		if(maybe_a_ship->player_name().get() == _player_name.get())
		{
			error_(
				error_code::name_not_available);
			return;
		}
	}

	// Now we know: There's no other player with that name. We can add
	// him/her!

	// Store these values here because we need them to create the model and
	// position/rotate it.
	model::position const pos(
		fcppt::math::box::center(
			this->play_area().get()));

	model::rotation const rot(
		0);

	fcppt::container::ptr::insert_unique_ptr_map(
		entities_,
		next_id_,
		fcppt::make_unique_ptr<entity::spaceship>(
			_player_name,
			pos,
			rot,
			this->play_area(),
			callbacks::insert_entity_function(
				std::tr1::bind(
					&object::insert_entity,
					this,
					std::tr1::placeholders::_1)),
			callbacks::change_position_function(
				std::tr1::bind(
					&object::change_entity_position,
					this,
					model::entity_id(
						next_id_),
					std::tr1::placeholders::_1)),
			callbacks::change_rotation_function(
				std::tr1::bind(
					&object::change_entity_rotation,
					this,
					model::entity_id(
						next_id_),
					std::tr1::placeholders::_1))));

	add_spaceship_(
		model::entity_id(
			next_id_),
		_player_name);

	position_entity_(
		model::entity_id(
			next_id_),
		pos);

	rotation_entity_(
		model::entity_id(
			next_id_),
		rot);

	next_id_++;
}

void
sgeroids::model::local::object::start_rotation(
	model::entity_id const &_id,
	model::rotation_direction const &_rotation)
{
	entity::spaceship &ship =
		this->search_spaceship_with_id(
			_id,
			local::error_context(
				FCPPT_TEXT("start_rotation")));

	 ship.start_rotation(
		 _rotation);
}

void
sgeroids::model::local::object::end_rotation(
	model::entity_id const &_id)
{
	entity::spaceship &ship =
		this->search_spaceship_with_id(
			_id,
			local::error_context(
				FCPPT_TEXT("end_rotation")));

	 ship.end_rotation();
}

void
sgeroids::model::local::object::change_thrust(
	model::entity_id const &_id,
	model::thrust const &_thrust)
{
	entity::spaceship &ship =
		this->search_spaceship_with_id(
			_id,
			local::error_context(
				FCPPT_TEXT("change_thrust")));

	 ship.thrust(
		 _thrust);
}

void
sgeroids::model::local::object::start_firing(
	model::entity_id const &_id)
{
	entity::spaceship &ship =
		this->search_spaceship_with_id(
			_id,
			local::error_context(
				FCPPT_TEXT("start_firing")));

	 ship.start_firing();
}

void
sgeroids::model::local::object::end_firing(
	model::entity_id const &_id)
{
	entity::spaceship &ship =
		this->search_spaceship_with_id(
			_id,
			local::error_context(
				FCPPT_TEXT("end_firing")));

	 ship.end_firing();
}

sgeroids::model::play_area const
sgeroids::model::local::object::play_area() const
{
	return
		sgeroids::model::play_area(
			sgeroids::rect(
				sgeroids::vector2(
					0,
					0),
				sgeroids::dim2(
					math::unit_magnitude() * 10000,
					math::unit_magnitude() * 10000)));
}

sgeroids::model::local::object::~object()
{
}

void
sgeroids::model::local::object::entity_updates()
{
	for(entity_map::iterator it = entities_.begin(); it != entities_.end();)
	{
		it->second->update();
		if(it->second->dead())
		{
			entity_map::iterator old_it = it;
			++it;
			entities_.erase(
				old_it);
		}
		else
		{
			++it;
		}
	}
}

void
sgeroids::model::local::object::collision_detection_broadphase()
{
	for(entity_map::const_iterator left = entities_.begin(); left != entities_.end(); ++left)
	{
		for(entity_map::const_iterator right = boost::next(left); right != entities_.end(); ++right)
		{
			this->collision_detection_narrow_phase(
				*(left->second),
				*(right->second));
		}
	}
}

void
sgeroids::model::local::object::collision_detection_narrow_phase(
	entity::base &_left,
	entity::base &_right)
{
	int const object_distance =
		fcppt::math::vector::length_quad(
			_left.position() - _right.position());

	int const sum_radii =
		_left.radius() + _right.radius();

	if(object_distance <= sum_radii*sum_radii)
	{
		_left.collides_with(
			_right);

		_right.collides_with(
			_left);
	}
}

sgeroids::model::local::entity::spaceship &
sgeroids::model::local::object::search_spaceship_with_id(
	model::entity_id const &_id,
	local::error_context const &_context)
{
	entity_map::iterator it =
		entities_.find(
			_id.get());

	if(it == entities_.end())
		throw
			sgeroids::exception(
				_context.get()+
				FCPPT_TEXT(": unknown entity id ")+
				fcppt::insert_to_fcppt_string(
					_id.get()));

	fcppt::optional<entity::spaceship &> maybe_a_ship(
		fcppt::optional_dynamic_cast<entity::spaceship &>(
			*(it->second)));

	 if(!maybe_a_ship)
			sgeroids::exception(
				_context.get()+FCPPT_TEXT(": The entity id ")+
				fcppt::insert_to_fcppt_string(
					_id.get())+
				FCPPT_TEXT(" refers to an entity of (invalid) type ")+
				fcppt::type_name(
					base_ref));

	 return *maybe_a_ship;
}

void
sgeroids::model::local::object::change_entity_position(
	model::entity_id const &_id,
	model::position const &_pos)
{
	position_entity_(
		_id,
		_pos);
}

void
sgeroids::model::local::object::change_entity_rotation(
	model::entity_id const &_id,
	model::rotation const &)
{
	rotation_entity_(
		_id,
		_pos);
}

void
sgeroids::model::local::object::insert_entity(
	entity::unique_base_ptr new_entity)
{
	fcppt::container::ptr::insert_unique_ptr_map(
		entities_,
		next_id_++,
		fcppt::move(
			new_entity));
}
