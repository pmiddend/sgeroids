#ifndef SGEROIDS_RANDOM_GENERATOR_FWD_HPP_INCLUDED
#define SGEROIDS_RANDOM_GENERATOR_FWD_HPP_INCLUDED

#include <fcppt/random/generator/minstd_rand_fwd.hpp>

namespace sgeroids
{
/**
\brief Define the random number generator type to use.

Better random generators give better randomness (srsly!).
*/
typedef
fcppt::random::generator::minstd_rand
random_generator;
}

#endif
