#include <fcppt/math/vector/arithmetic.hpp>
#include <sgeroids/model/local/asteroid_generator/play_area_side.hpp>
#include <sgeroids/math/discrete_sin.hpp>
#include <sgeroids/math/discrete_cos.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <sgeroids/model/vector2.hpp>
#include <sgeroids/math/unit_magnitude.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <sgeroids/model/local/asteroid_generator/object.hpp>

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
		fcppt::random::make_inclusive_range<unsigned>(
			2*60,
			6*60),
		_rng),
	radius_rng_(
		fcppt::random::make_inclusive_range<int>(
			math::unit_magnitude() * 30000,
			math::unit_magnitude() * 120000),
		_rng),
	rotation_rng_(
		fcppt::random::make_inclusive_range<int>(
			0,
			360 * sgeroids::math::unit_magnitude()),
		_rng),
	rotation_direction_rng_(
		fcppt::random::make_inclusive_range<int>(
			-sgeroids::math::unit_magnitude(),
			sgeroids::math::unit_magnitude()),
		_rng),
	velocity_angle_rng_(
		fcppt::random::make_inclusive_range<int>(
			0,
			360),
		_rng),
	velocity_magnitude_rng_(
		fcppt::random::make_inclusive_range<int>(
			0,
			100 * sgeroids::math::unit_magnitude()),
		_rng),
	play_area_side_rng_(
		fcppt::random::make_inclusive_range<int>(
			0,
			3),
		_rng),
	play_area_x_rng_(
		fcppt::random::make_inclusive_range<int>(
			play_area_.left(),
			play_area_.right()),
		_rng),
	play_area_y_rng_(
		fcppt::random::make_inclusive_range<int>(
			play_area_.top(),
			play_area_.bottom()),
		_rng),
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
	play_area_side::type const chosen_side =
		static_cast<play_area_side::type>(
			play_area_side_rng_());

	int const chosen_radius =
		radius_rng_();

	model::vector2 chosen_position;

	switch(chosen_side)
	{
		case play_area_side::left:
			chosen_position.x() =
				play_area_.left() - chosen_radius;

			chosen_position.y() =
				play_area_y_rng_();
			break;
		case play_area_side::right:
			chosen_position.x() =
				play_area_.right() + chosen_radius;

			chosen_position.y() =
				play_area_y_rng_();
			break;
		case play_area_side::top:
			chosen_position.y() =
				play_area_.top() - chosen_radius;

			chosen_position.x() =
				play_area_x_rng_();
			break;
		case play_area_side::bottom:
			chosen_position.y() =
				play_area_.bottom() + chosen_radius;

			chosen_position.x() =
				play_area_x_rng_();
			break;
	}

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
					chosen_velocity_angle),
				math::discrete_sin(
					chosen_velocity_angle))));
}

sgeroids::model::local::asteroid_generator::object::~object()
{
}
