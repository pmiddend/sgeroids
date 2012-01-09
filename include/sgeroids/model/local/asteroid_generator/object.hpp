#ifndef SGEROIDS_MODEL_LOCAL_ASTEROID_GENERATOR_OBJECT_HPP_INCLUDED
#define SGEROIDS_MODEL_LOCAL_ASTEROID_GENERATOR_OBJECT_HPP_INCLUDED

#include <sgeroids/model/local/callbacks/asteroid_generation.hpp>
#include <sgeroids/model/play_area.hpp>
#include <sgeroids/random_generator.hpp>
#include <fcppt/random/uniform.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sgeroids
{
namespace model
{
namespace local
{
namespace asteroid_generator
{
/**
\brief Handles timing and creation of asteroids

The \link sgeroids::model::local::asteroid_generator::update update \endlink
function checks if the current countdown has expired. If it has expired, new
random values for the asteroids are generated. The generator then calls the
asteroid generation callback.

The asteroid generator thus doesn't actually generate asteroid <em>instances</em>,
just the <em>parameters</em> for their creation. The model actually
instantiates the asteroid entity (or whoever is behind the callback).

The timer is just a number right now: It's initialized with a positive value
and is decremented at each update call. If it reaches zero, it's expired.

\note
Instead of receiving a callback function, the generator could have a signal.
There's no special reason why I chose the callback, it's just convenient for
now.
*/
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	/**
	\brief Creates the generator, initializes the first countdown
	*/
	explicit
	object(
		sgeroids::random_generator &,
		model::play_area const &,
		local::callbacks::asteroid_generation const &);

	/**
	\brief Update the generation timer, create a new asteroid if it expired. Then reinitialize the timer.
	*/
	void
	update();

	/**
	\brief Dummy destructor because of noncopyable class
	*/
	~object();
private:
	model::rect const play_area_;
	local::callbacks::asteroid_generation asteroid_generation_;
	fcppt::random::uniform<unsigned,sgeroids::random_generator &> next_asteroid_duration_rng_;
	fcppt::random::uniform<int,sgeroids::random_generator &> radius_rng_;
	// Initial rotation
	fcppt::random::uniform<int,sgeroids::random_generator &> rotation_rng_;
	// Rotation velocity
	fcppt::random::uniform<int,sgeroids::random_generator &> rotation_direction_rng_;
	// The velocity is generated using polar coordinates, so we need a
	// magnitude and an angle. This is the angle...
	fcppt::random::uniform<int,sgeroids::random_generator &> velocity_angle_rng_;
	// ...and this is the magnitude.
	fcppt::random::uniform<int,sgeroids::random_generator &> velocity_magnitude_rng_;
	// Which side (left, right, top, bottom)
	fcppt::random::uniform<int,sgeroids::random_generator &> play_area_side_rng_;
	// The x coordinate (inside the play area)
	fcppt::random::uniform<int,sgeroids::random_generator &> play_area_x_rng_;
	// The y coordinate (inside the play area)
	fcppt::random::uniform<int,sgeroids::random_generator &> play_area_y_rng_;
	unsigned next_asteroid_countdown_;
};
}
}
}
}

#endif
