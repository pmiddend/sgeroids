#include <sgeroids/random_generator_seed.hpp>
#include <fcppt/chrono/high_resolution_clock.hpp>
#include <fcppt/chrono/time_point_impl.hpp>
#include <fcppt/chrono/duration_impl.hpp>

sgeroids::random_generator::result_type
sgeroids::random_generator_seed()
{
	return
		static_cast<sgeroids::random_generator::result_type>(
			fcppt::chrono::high_resolution_clock::now().time_since_epoch().count());
}
