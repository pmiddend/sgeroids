#include <fcppt/assert/unreachable.hpp>
#include <sgeroids/exception.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/model/local/object.hpp>
#include <sgeroids/model/vector2.hpp>
#include <sgeroids/model/dim2.hpp>
#include <sgeroids/model/log.hpp>
#include <sgeroids/model/local/entity/spaceship.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/move.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/optional_dynamic_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/center.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/length_square.hpp>
#include <fcppt/tr1/functional.hpp>
#include <typeinfo>

sgeroids::model::local::object::object()
:
	next_id_(
		0u),
	entities_(),
	add_spaceship_(),
	add_asteroid_(),
	add_projectile_(),
	collide_projectile_asteroid_(),
	score_change_(),
	destroy_asteroid_(),
	remove_entity_(),
	position_entity_(),
	rotation_entity_(),
	gameover_(),
	error_()
{
}

void
sgeroids::model::local::object::update()
{
	this->entity_updates();
	this->collision_detection_broadphase();
}

fcppt::signal::auto_connection
sgeroids::model::local::object::add_spaceship_callback(
	model::callbacks::add_spaceship const &_f)
{
	return
		add_spaceship_.connect(
			_f);
}

fcppt::signal::auto_connection
sgeroids::model::local::object::add_asteroid_callback(
	model::callbacks::add_asteroid const &_f)
{
	return
		add_asteroid_.connect(
			_f);
}

fcppt::signal::auto_connection
sgeroids::model::local::object::add_projectile_callback(
	model::callbacks::add_projectile const &_f)
{
	return
		add_projectile_.connect(
			_f);
}

fcppt::signal::auto_connection
sgeroids::model::local::object::collide_projectile_asteroid_callback(
	model::callbacks::collide_projectile_asteroid const &_f)
{
	return
		collide_projectile_asteroid_.connect(
			_f);
}

fcppt::signal::auto_connection
sgeroids::model::local::object::score_change_callback(
	model::callbacks::score_change const &_f)
{
	return
		score_change_.connect(
			_f);
}

fcppt::signal::auto_connection
sgeroids::model::local::object::destroy_asteroid_callback(
	model::callbacks::destroy_asteroid const &_f)
{
	return
		destroy_asteroid_.connect(
			_f);
}

fcppt::signal::auto_connection
sgeroids::model::local::object::remove_entity_callback(
	model::callbacks::remove_entity const &_f)
{
	return
		remove_entity_.connect(
			_f);
}

fcppt::signal::auto_connection
sgeroids::model::local::object::position_entity_callback(
	model::callbacks::position_entity const &_f)
{
	return
		position_entity_.connect(
			_f);
}

fcppt::signal::auto_connection
sgeroids::model::local::object::rotation_entity_callback(
	model::callbacks::rotation_entity const &_f)
{
	return
		rotation_entity_.connect(
			_f);
}

fcppt::signal::auto_connection
sgeroids::model::local::object::gameover_callback(
	model::callbacks::gameover const &_f)
{
	return
		gameover_.connect(
			_f);
}

fcppt::signal::auto_connection
sgeroids::model::local::object::error_callback(
	model::callbacks::error const &_f)
{
	return
		error_.connect(
			_f);
}

void
sgeroids::model::local::object::add_player(
	model::player_name const &_player_name)
{
	FCPPT_LOG_DEBUG(
		model::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Adding player ")
			<< _player_name.get());

	// First, search for a player with the given name. If one already
	// exists, we have to signal an error.
	for(
		entity_map::const_iterator it =
			entities_.begin();
		it != entities_.end();
		++it)
	{
		fcppt::optional<entity::spaceship const &> maybe_a_ship(
			fcppt::optional_dynamic_cast<entity::spaceship const &>(
				*(it->second)));

		if(!maybe_a_ship)
			continue;

		if(maybe_a_ship->player_name().get() == _player_name.get())
		{
			FCPPT_LOG_DEBUG(
				model::log(),
				fcppt::log::_
					<< FCPPT_TEXT("Got add_player with existing player name ")
					<< _player_name.get());

			error_(
				error_code::name_not_available);

			return;
		}
	}

	// Now we know: There's no other player with that name. We can add
	// him/her!

	// Store these values here because we need them to create the model and
	// position/rotate it.
	model::position const ship_position(
		fcppt::math::box::center(
			this->play_area().get()));

	model::rotation const ship_rotation(
		0);

	fcppt::unique_ptr<entity::spaceship> to_add(
		fcppt::make_unique_ptr<entity::spaceship>(
			_player_name,
			ship_position,
			ship_rotation,
			this->play_area(),
			local::callbacks::position_entity_no_id(
				std::tr1::bind(
					&object::change_entity_position,
					this,
					model::entity_id(
						next_id_),
					std::tr1::placeholders::_1)),
			local::callbacks::rotation_entity_no_id(
				std::tr1::bind(
					&object::change_entity_rotation,
					this,
					model::entity_id(
						next_id_),
					std::tr1::placeholders::_1))));

	model::radius const ship_radius =
		to_add->radius();

	fcppt::container::ptr::insert_unique_ptr_map(
		entities_,
		next_id_,
		fcppt::move(
			to_add));

	FCPPT_LOG_DEBUG(
		model::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Sending add_spaceship signal."));

	add_spaceship_(
		model::entity_id(
			next_id_),
		ship_radius,
		_player_name);

	position_entity_(
		model::entity_id(
			next_id_),
		ship_position);

	rotation_entity_(
		model::entity_id(
			next_id_),
		ship_rotation);

	next_id_++;
}

void
sgeroids::model::local::object::remove_player(
	model::player_name const &_player_name)
{
	FCPPT_LOG_DEBUG(
		model::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Removing the player: ") << _player_name.get());

	for(
		entity_map::iterator it =
			entities_.begin();
		it != entities_.end();
		++it)
	{
		fcppt::optional<entity::spaceship const &> maybe_a_ship(
			fcppt::optional_dynamic_cast<entity::spaceship const &>(
				*(it->second)));

		if(!maybe_a_ship)
			continue;

		FCPPT_LOG_DEBUG(
			model::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Testing the ship ") << maybe_a_ship->player_name().get());

		if(maybe_a_ship->player_name().get() == _player_name.get())
		{
			remove_entity_(
				model::entity_id(
					it->first));
			entities_.erase(
				it);
			return;
		}
	}

	FCPPT_ASSERT_UNREACHABLE;
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
			sgeroids::model::rect(
				sgeroids::model::vector2(
					0,
					0),
				sgeroids::model::dim2(
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
	for(entity_map::iterator left = entities_.begin(); left != entities_.end(); ++left)
	{
		for(entity_map::iterator right = boost::next(left); right != entities_.end(); ++right)
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
		fcppt::math::vector::length_square(
			_left.position().get() - _right.position().get());

	int const sum_radii =
		_left.radius().get() + _right.radius().get();

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
					typeid(
						*(it->second))));

	 return *maybe_a_ship;
}

void
sgeroids::model::local::object::change_entity_position(
	model::entity_id const &_id,
	model::position const &_position)
{
	position_entity_(
		_id,
		_position);
}

void
sgeroids::model::local::object::change_entity_rotation(
	model::entity_id const &_id,
	model::rotation const &_rotation)
{
	rotation_entity_(
		_id,
		_rotation);
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
