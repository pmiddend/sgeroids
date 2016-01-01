#include <sgeroids/exception.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/model/dim2.hpp>
#include <sgeroids/model/error_code.hpp>
#include <sgeroids/model/log.hpp>
#include <sgeroids/model/score.hpp>
#include <sgeroids/model/spaceship_id.hpp>
#include <sgeroids/model/vector2.hpp>
#include <sgeroids/model/local/object.hpp>
#include <sgeroids/model/local/asteroid_generator/object.hpp>
#include <sgeroids/model/local/callbacks/asteroid_generation.hpp>
#include <sgeroids/model/local/entity/asteroid.hpp>
#include <sgeroids/model/local/entity/projectile.hpp>
#include <sgeroids/model/local/entity/spaceship.hpp>
#include <alda/message/make_concrete_ptr.hpp>
#include <alda/serialization/serialize.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/maybe_void_multi.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/try_dynamic.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/math/box/center.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <array>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <typeinfo>
#include <utility>
#include <fcppt/config/external_end.hpp>


sgeroids::model::local::object::object(
	std::ostream &_serialization_output)
:
	serialization_output_(
		_serialization_output),
	rng_(),
	next_id_(
		0u),
	entities_(),
	asteroid_generator_(),
	add_spaceship_(),
	remove_spaceship_(),
	add_asteroid_(),
	add_projectile_(),
	collide_projectile_asteroid_(),
	score_change_(),
	destroy_asteroid_(),
	remove_entity_(),
	position_entity_(),
	rotation_entity_(),
	gameover_(),
	error_(),
	change_thrust_()
{
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
sgeroids::model::local::object::remove_spaceship_callback(
	model::callbacks::remove_spaceship const &_f)
{
	return
		remove_spaceship_.connect(
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

fcppt::signal::auto_connection
sgeroids::model::local::object::change_thrust_callback(
	model::callbacks::change_thrust const &_f)
{
	return
		change_thrust_.connect(
			_f);
}

void
sgeroids::model::local::object::process_message(
	sgeroids::model::serialization::message::rng_seed const &_message)
{
	alda::serialization::serialize(
		serialization_output_,
		*alda::message::make_concrete_ptr<sgeroids::model::serialization::message::adapted_types::message>(
			_message));

	random_generator_unique_ptr const &rng(
		fcppt::optional::assign(
			rng_,
			fcppt::make_unique_ptr<
				sgeroids::random_generator
			>(
				sgeroids::random_generator::seed(
					_message.get<
						sgeroids::model::serialization::message::roles::seed
					>()
				)
			)
		)
	);

	asteroid_generator_ =
		optional_asteroid_generator_unique_ptr(
			fcppt::make_unique_ptr<
				sgeroids::model::local::asteroid_generator::object
			>(
				*rng,
				this->play_area(),
				sgeroids::model::local::callbacks::asteroid_generation{
					std::bind(
						&object::asteroid_generated,
						this,
						std::placeholders::_1,
						std::placeholders::_2,
						std::placeholders::_3,
						std::placeholders::_4,
						std::placeholders::_5
					)
				}
			)
		);
}

void
sgeroids::model::local::object::process_message(
	sgeroids::model::serialization::message::update const &_message)
{
	alda::serialization::serialize(
		serialization_output_,
		*alda::message::make_concrete_ptr<sgeroids::model::serialization::message::adapted_types::message>(
			_message));

	this->entity_updates();
	this->collision_detection_broadphase();

	fcppt::optional::maybe_void(
		asteroid_generator_,
		[](
			asteroid_generator_unique_ptr const &_generator
		)
		{
			_generator->update();
		}
	);
}

void
sgeroids::model::local::object::process_message(
	sgeroids::model::serialization::message::add_player const &_message)
{
	alda::serialization::serialize(
		serialization_output_,
		*alda::message::make_concrete_ptr<sgeroids::model::serialization::message::adapted_types::message>(
			_message));

	sgeroids::model::player_name const player_name(
		_message.get<sgeroids::model::serialization::message::roles::player_name>());

	FCPPT_LOG_DEBUG(
		model::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Adding new player"));

	// First, search for a player with the given name. If one already
	// exists, we have to signal an error.
	for(
		auto const &entity
		:
		entities_
	)
	{
		fcppt::optional::maybe_void(
			fcppt::cast::try_dynamic<
				sgeroids::model::local::entity::spaceship const &
			>(
				*entity.second
			),
			[
				&player_name,
				this
			](
				sgeroids::model::local::entity::spaceship const &_maybe_a_ship
			)
			{
				if(_maybe_a_ship.player_name().get() == player_name.get())
				{
					FCPPT_LOG_DEBUG(
						model::log(),
						fcppt::log::_
							<< FCPPT_TEXT("Got add_player with existing player name"));

					error_(
						sgeroids::model::error_code::name_not_available);

					return;
				}
			}
		);
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

	fcppt::unique_ptr<
		sgeroids::model::local::entity::spaceship
	> to_add(
		fcppt::make_unique_ptr<
			sgeroids::model::local::entity::spaceship
		>(
			player_name,
			ship_position,
			ship_rotation,
			this->play_area(),
			local::callbacks::position_entity_no_id(
				std::bind(
					&object::change_entity_position,
					this,
					model::entity_id(
						next_id_),
					std::placeholders::_1)),
			local::callbacks::rotation_entity_no_id(
				std::bind(
					&object::change_entity_rotation,
					this,
					model::entity_id(
						next_id_),
					std::placeholders::_1)),
			local::callbacks::insert_projectile(
				std::bind(
					&object::insert_projectile,
					this,
					model::spaceship_id(
						next_id_),
					std::placeholders::_1,
					std::placeholders::_2
				)
			)
		)
	);

	model::radius const ship_radius{
		to_add->radius()
	};

	entities_.emplace(
		next_id_,
		fcppt::unique_ptr_to_base<
			sgeroids::model::local::entity::base
		>(
			std::move(
				to_add
			)
		)
	);

	FCPPT_LOG_DEBUG(
		model::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Sending add_spaceship signal."));

	add_spaceship_(
		model::entity_id(
			next_id_),
		ship_radius,
		player_name);

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
sgeroids::model::local::object::process_message(
	sgeroids::model::serialization::message::remove_player const &_message)
{
	alda::serialization::serialize(
		serialization_output_,
		*alda::message::make_concrete_ptr<sgeroids::model::serialization::message::adapted_types::message>(
			_message));

	sgeroids::model::player_name const player_name(
		_message.get<sgeroids::model::serialization::message::roles::player_name>());

	FCPPT_LOG_DEBUG(
		model::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Removing a player"));

	for(
		auto const &entity
		:
		entities_
	)
	{
		fcppt::optional::maybe_void(
			fcppt::cast::try_dynamic<entity::spaceship &>(
				*entity.second
			),
			[
				&player_name
			](
				entity::spaceship &_maybe_a_ship
			)
			{
				/*
				FCPPT_LOG_DEBUG(
					model::log(),
					fcppt::log::_
						<< FCPPT_TEXT("Testing the ship ") << maybe_a_ship->player_name().get());
						*/

				if(_maybe_a_ship.player_name().get() == player_name.get())
					_maybe_a_ship.kill();
			}
		);
	}
}

void
sgeroids::model::local::object::process_message(
	sgeroids::model::serialization::message::rotation_direction const &_message)
{
	alda::serialization::serialize(
		serialization_output_,
		*alda::message::make_concrete_ptr<sgeroids::model::serialization::message::adapted_types::message>(
			_message));

	model::entity_id const id(
		_message.get<sgeroids::model::serialization::message::roles::entity_id>());

	model::rotation_direction const rotation_direction(
		_message.get<sgeroids::model::serialization::message::roles::rotation_direction>());

	entity::spaceship &ship =
		this->find_spaceship_by_id_exn(
			id,
			local::error_context(
				FCPPT_TEXT("rotation_direction")));

	 ship.rotation_direction(
		 rotation_direction);
}

void
sgeroids::model::local::object::process_message(
	sgeroids::model::serialization::message::change_thrust const &_message)
{
	alda::serialization::serialize(
		serialization_output_,
		*alda::message::make_concrete_ptr<sgeroids::model::serialization::message::adapted_types::message>(
			_message));

	model::entity_id const id(
		_message.get<sgeroids::model::serialization::message::roles::entity_id>());

	model::thrust const thrust(
		_message.get<sgeroids::model::serialization::message::roles::thrust>());

	entity::spaceship &ship =
		this->find_spaceship_by_id_exn(
			id,
			local::error_context(
				FCPPT_TEXT("change_thrust")));

	 ship.thrust(
		 thrust);

	 change_thrust_(
		 id,
		 thrust);
}

void
sgeroids::model::local::object::process_message(
	sgeroids::model::serialization::message::change_firing_mode const &_message)
{
	alda::serialization::serialize(
		serialization_output_,
		*alda::message::make_concrete_ptr<sgeroids::model::serialization::message::adapted_types::message>(
			_message));

	model::entity_id const id(
		_message.get<sgeroids::model::serialization::message::roles::entity_id>());

	model::firing_mode const firing_mode(
		static_cast<model::firing_mode>(
			_message.get<sgeroids::model::serialization::message::roles::firing_mode>()));

	entity::spaceship &ship =
		this->find_spaceship_by_id_exn(
			id,
			local::error_context(
				FCPPT_TEXT("change_firing_mode")));

	 ship.change_firing_mode(
		 firing_mode);
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
					math::unit_magnitude() * 2000000,
					math::unit_magnitude() * 2000000)));
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
			fcppt::optional::maybe_void(
				fcppt::cast::try_dynamic<entity::spaceship &>(
					*(it->second)
				),
				[
					this
				](
					entity::spaceship &_maybe_ship
				)
				{
					remove_spaceship_(
						_maybe_ship.player_name());
				}
			);

			remove_entity_(
				model::entity_id(
					it->first));

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
		for(entity_map::iterator right = std::next(left); right != entities_.end(); ++right)
		{
			this->collision_detection_narrow_phase(
				*(left->second),
				model::entity_id(
					left->first),
				*(right->second),
				model::entity_id(
					right->first));
		}
	}
}

void
sgeroids::model::local::object::collision_detection_narrow_phase(
	entity::base &_left,
	model::entity_id const &_left_id,
	entity::base &_right,
	model::entity_id const &_right_id)
{
	model::vector2 const
		difference_vector =
			_left.position().get() - _right.position().get();

	int const
		sum_radii =
			_left.radius().get() + _right.radius().get(),
		maximum_norm =
			std::max(
				std::abs(
					difference_vector.x()),
				std::abs(
					difference_vector.y()));

	if(maximum_norm <= sum_radii)
	{
		_left.collides_with(
			_right);

		_right.collides_with(
			_left);

		fcppt::optional::maybe_void_multi(
			[
				_left_id,
				_right_id,
				this
			](
				sgeroids::model::local::entity::asteroid const &,
				sgeroids::model::local::entity::projectile const &
			)
			{
				collide_projectile_asteroid_(
					model::projectile_id(
						_right_id.get()),
					model::asteroid_id(
						_left_id.get()));
			},
			fcppt::cast::try_dynamic<entity::asteroid const &>(
				_left
			),
			fcppt::cast::try_dynamic<entity::projectile const &>(
				_right
			)
		);

		fcppt::optional::maybe_void_multi(
			[
				_left_id,
				_right_id,
				this
			](
				sgeroids::model::local::entity::projectile const &,
				sgeroids::model::local::entity::asteroid const &
			)
			{
				collide_projectile_asteroid_(
					model::projectile_id(
						_left_id.get()),
					model::asteroid_id(
						_right_id.get()));
			},
			fcppt::cast::try_dynamic<entity::projectile const &>(
				_left
			),
			fcppt::cast::try_dynamic<entity::asteroid const &>(
				_right
			)
		);
	}
}

fcppt::optional::object<
	sgeroids::model::local::entity::spaceship &
>
sgeroids::model::local::object::find_spaceship_by_id(
	sgeroids::model::spaceship_id const &_id)
{
	entity_map::iterator it =
		entities_.find(
			_id.get());

	if(it == entities_.end())
		return
			fcppt::optional::object<
				sgeroids::model::local::entity::spaceship &
			>();

	fcppt::optional::object<entity::spaceship &> maybe_a_ship(
		fcppt::cast::try_dynamic<entity::spaceship &>(
			*(it->second)));

	 return maybe_a_ship;
}

sgeroids::model::local::entity::spaceship &
sgeroids::model::local::object::find_spaceship_by_id_exn(
	sgeroids::model::entity_id const &_id,
	sgeroids::model::local::error_context const &_context
)
{
	return
		fcppt::optional::to_exception(
			fcppt::cast::try_dynamic<
				sgeroids::model::local::entity::spaceship &
			>(
				*fcppt::optional::to_exception(
					fcppt::container::find_opt_mapped(
						entities_,
						_id.get()
					),
					[
						_id,
						&_context
					]{
						return
							sgeroids::exception(
								_context.get()
								+
								FCPPT_TEXT(": unknown entity id ")
								+
								fcppt::insert_to_fcppt_string(
									_id.get()
								)
							);
					}
				)
			),
			[
				_id,
				&_context
			]{
				return
					sgeroids::exception(
						_context.get()
						+
						FCPPT_TEXT(": The entity id ")
						+
						fcppt::insert_to_fcppt_string(
							_id.get()
						)
						+
						FCPPT_TEXT(" refers to an entity of (invalid) type ")
					);
			}
		);
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
	entities_.insert(
		std::make_pair(
			next_id_++,
			std::move(
				new_entity)));
}

void
sgeroids::model::local::object::asteroid_generated(
	model::position const &_position,
	model::rotation const &_rotation,
	model::rotation_direction const &_rotation_direction,
	model::radius const &_radius,
	model::velocity const &_velocity)
{
	FCPPT_LOG_DEBUG(
		model::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Got an asteroid generation, creating entity"));

	entities_.emplace(
		next_id_,
		fcppt::unique_ptr_to_base<
			sgeroids::model::local::entity::base
		>(
			fcppt::make_unique_ptr<
				entity::asteroid
			>(
				_position,
				_rotation,
				_rotation_direction,
				_radius,
				this->play_area(),
				_velocity,
				local::callbacks::position_entity_no_id(
					std::bind(
						&object::change_entity_position,
						this,
						model::entity_id(
							next_id_),
						std::placeholders::_1)),
				local::callbacks::rotation_entity_no_id(
					std::bind(
						&object::change_entity_rotation,
						this,
						model::entity_id(
							next_id_),
						std::placeholders::_1)),
				local::callbacks::asteroid_died(
					std::bind(
						&object::asteroid_died,
						this,
						model::entity_id(
							next_id_),
						std::placeholders::_1,
						std::placeholders::_2
					)
				)
			)
		)
	);

	add_asteroid_(
		model::entity_id(
			next_id_),
		_radius);

	position_entity_(
		model::entity_id(
			next_id_),
		_position);

	rotation_entity_(
		model::entity_id(
			next_id_),
		_rotation);

	next_id_++;
}

void
sgeroids::model::local::object::insert_projectile(
	model::spaceship_id const &_owner_id,
	model::position const &_position,
	model::rotation const &_rotation)
{
	FCPPT_LOG_DEBUG(
		model::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Inserting projectile"));

	fcppt::unique_ptr<
		entity::projectile
	> to_add(
		fcppt::make_unique_ptr<
			entity::projectile
		>(
			_position,
			_rotation,
			this->play_area(),
			_owner_id,
			local::callbacks::position_entity_no_id(
				std::bind(
					&object::change_entity_position,
					this,
					model::entity_id(
						next_id_),
					std::placeholders::_1)),
			local::callbacks::rotation_entity_no_id(
				std::bind(
					&object::change_entity_rotation,
					this,
					model::entity_id(
						next_id_),
					std::placeholders::_1))));

	model::radius const radius{
		to_add->radius()
	};

	entities_.emplace(
		next_id_,
		fcppt::unique_ptr_to_base<
			sgeroids::model::local::entity::base
		>(
			std::move(
				to_add
			)
		)
	);

	add_projectile_(
		model::entity_id(
			next_id_),
		radius);

	position_entity_(
		model::entity_id(
			next_id_),
		_position);

	rotation_entity_(
		model::entity_id(
			next_id_),
		_rotation);

	next_id_++;
}

void
sgeroids::model::local::object::asteroid_died(
	model::entity_id const &_entity_id,
	local::entity::asteroid &_asteroid,
	model::spaceship_id const &_killer_id)
{
	FCPPT_LOG_DEBUG(
		model::log(),
		fcppt::log::_
			<< FCPPT_TEXT("An asteroid died, checking if we need to create another one"));

	fcppt::optional::maybe_void(
		this->find_spaceship_by_id(
			_killer_id
		),
		[
			_killer_id,
			this
		](
			sgeroids::model::local::entity::spaceship &_killer
		)
		{
			_killer.increase_score(
				sgeroids::model::score(
					100
				)
			);

			score_change_(
				_killer_id,
				_killer.score()
			);
		}
	);

	destroy_asteroid_(
		_entity_id);

	model::vector2 const
		original_velocity(
			_asteroid.velocity().get());

	typedef
	std::array<model::velocity,2>
	velocity_array;

	velocity_array const normals{{
		model::velocity(
			model::vector2(
				-original_velocity.y(),
				original_velocity.x())),
		model::velocity(
			model::vector2(
				original_velocity.y(),
				-original_velocity.x()))
	}};

	model::position const new_position(
		_asteroid.position());

	model::rotation const new_rotation(
		_asteroid.rotation());

	model::rotation_direction const new_rotation_direction(
		_asteroid.rotation_direction());

	model::radius const new_radius(
		_asteroid.radius().get()/2);

	for(
		auto const &new_velocity
		:
		normals
	)
	{

		entities_.emplace(
			next_id_,
			fcppt::unique_ptr_to_base<
				sgeroids::model::local::entity::base
			>(
				fcppt::make_unique_ptr<
					sgeroids::model::local::entity::asteroid
				>(
					new_position,
					new_rotation,
					new_rotation_direction,
					new_radius,
					this->play_area(),
					new_velocity,
					local::callbacks::position_entity_no_id(
						std::bind(
							&object::change_entity_position,
							this,
							model::entity_id(
								next_id_),
							std::placeholders::_1)),
					local::callbacks::rotation_entity_no_id(
						std::bind(
							&object::change_entity_rotation,
							this,
							model::entity_id(
								next_id_),
							std::placeholders::_1)),
					local::callbacks::asteroid_died(
						std::bind(
							&object::asteroid_died,
							this,
							model::entity_id(
								next_id_),
							std::placeholders::_1,
							std::placeholders::_2
						)
					)
				)
			)
		);

		add_asteroid_(
			model::entity_id(
				next_id_),
			new_radius);

		position_entity_(
			model::entity_id(
				next_id_),
			new_position);

		rotation_entity_(
			model::entity_id(
				next_id_),
			new_rotation);

		next_id_++;
	}
}
