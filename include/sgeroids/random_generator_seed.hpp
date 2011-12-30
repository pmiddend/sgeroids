#ifndef SGEROIDS_RANDOM_GENERATOR_SEED_HPP_INCLUDED
#define SGEROIDS_RANDOM_GENERATOR_SEED_HPP_INCLUDED

#include <sgeroids/random_generator.hpp>

namespace sgeroids
{
/**
\brief Generates a seed for the random number generator

There are multiple ways in which a random number generator might be seeded. In
Linux, you can read bytes from <code>/dev/random</code> or
<code>/dev/urandom</code> or you could take the current time in microseconds.
This function generates a seed using chrono's high resolution clock (but that
might change in the future).
*/
sgeroids::random_generator::result_type
random_generator_seed();
}

#endif
