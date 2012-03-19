#include <sgeroids/random_generator.hpp>
#include <sgeroids/random_generator_seed.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>


sgeroids::random_generator::seed const
sgeroids::random_generator_seed()
{
	return
		fcppt::random::generator::seed_from_chrono<
			sgeroids::random_generator::seed
		>();
}
