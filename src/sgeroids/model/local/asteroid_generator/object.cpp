#include <sgeroids/random_generator.hpp>
#include <sgeroids/math/discrete_cos.hpp>
#include <sgeroids/math/discrete_sin.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <sgeroids/model/vector2.hpp>
#include <sgeroids/model/local/asteroid_generator/object.hpp>
#include <sgeroids/model/local/asteroid_generator/play_area_side.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_impl.hpp>


sgeroids::model::local::asteroid_generator::object::object(
	sgeroids::random_generator &_rng,
	model::play_area const &_play_area,
	local::callbacks::asteroid_generation const &_asteroid_generation)
:
	play_area_(
		_play_area.get()),
	asteroid_generation_(
		_asteroid_generation),
	next_asteroid_duration_rng_(
		_rng,
		uint_distribution(
			uint_distribution::param_type::min(
				2u*60u),
			uint_distribution::param_type::max(
				6u*60u))),
	radius_rng_(
		_rng,
		int_distribution(
			int_distribution::param_type::min(
				math::unit_magnitude() * 30000),
			int_distribution::param_type::max(
				math::unit_magnitude() * 120000))),
	rotation_rng_(
		_rng,
		int_distribution(
			int_distribution::param_type::min(
				0),
			int_distribution::param_type::max(
				360 * sgeroids::math::unit_magnitude()))),
	rotation_direction_rng_(
		_rng,
		int_distribution(
			int_distribution::param_type::min(
				-sgeroids::math::unit_magnitude()),
			int_distribution::param_type::max(
				sgeroids::math::unit_magnitude()))),
	velocity_angle_rng_(
		_rng,
		int_distribution(
			int_distribution::param_type::min(
				0),
			int_distribution::param_type::max(
				360))),
	velocity_magnitude_rng_(
		_rng,
		int_distribution(
			int_distribution::param_type::min(
				0),
			int_distribution::param_type::max(
				10 * sgeroids::math::unit_magnitude()))),
	play_area_side_rng_(
		_rng,
		int_distribution(
			int_distribution::param_type::min(
				0),
			// TODO: magic constant?
			int_distribution::param_type::max(
				3))),
	play_area_x_rng_(
		_rng,
		int_distribution(
			int_distribution::param_type::min(
				play_area_.left()),
			int_distribution::param_type::max(
				play_area_.right()))),
	play_area_y_rng_(
		_rng,
		int_distribution(
			int_distribution::param_type::min(
				play_area_.top()),
			int_distribution::param_type::max(
				play_area_.bottom()))),
	next_asteroid_countdown_(
		next_asteroid_duration_rng_())
{
}

void
sgeroids::model::local::asteroid_generator::object::update()
{
	// Timer not expired (still positive), then do nothing
	if(next_asteroid_countdown_)
	{
		--next_asteroid_countdown_;
		return;
	}

	next_asteroid_countdown_ =
		next_asteroid_duration_rng_();

	// The position is generated as follows:
	//
	// - First, choose a one of the four sides of the play area (left, right,
	//   top, bottom)
	// - Then, generate the according x/y coordinate (x for top and bottom,
	//   y for left and right)
	play_area_side const chosen_side =
		static_cast<play_area_side>(
			play_area_side_rng_());

	int const chosen_radius =
		radius_rng_();

	sgeroids::model::vector2 const chosen_position(
		[
			chosen_side,
			chosen_radius,
			this
		]{
			switch(chosen_side)
			{
				case play_area_side::left:
					return
						sgeroids::model::vector2(
							play_area_.left() - chosen_radius,
							play_area_y_rng_()
						);
				case play_area_side::right:
					return
						sgeroids::model::vector2(
							play_area_.right() + chosen_radius,
							play_area_y_rng_()
						);
				case play_area_side::top:
					return
						sgeroids::model::vector2(
							play_area_x_rng_(),
							play_area_.top() - chosen_radius
						);
				case play_area_side::bottom:
					return
						sgeroids::model::vector2(
							play_area_x_rng_(),
							play_area_.bottom() + chosen_radius
						);
			}

			FCPPT_ASSERT_UNREACHABLE;
		}()
	);

	int const chosen_velocity_angle =
		velocity_angle_rng_();

	asteroid_generation_(
		model::position(
			chosen_position),
		model::rotation(
			rotation_rng_()),
		model::rotation_direction(
			rotation_direction_rng_()),
		model::radius(
			chosen_radius),
		model::velocity(
			velocity_magnitude_rng_() *
			model::vector2(
				math::discrete_cos(
					math::degrees(
						chosen_velocity_angle)),
				math::discrete_sin(
					math::degrees(
						chosen_velocity_angle)))));
}

sgeroids::model::local::asteroid_generator::object::~object()
{
}
