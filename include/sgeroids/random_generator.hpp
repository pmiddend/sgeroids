#ifndef SGEROIDS_RANDOM_GENERATOR_HPP_INCLUDED
#define SGEROIDS_RANDOM_GENERATOR_HPP_INCLUDED

#include <fcppt/random/default_generator.hpp>

namespace sgeroids
{
/**
\brief Define the random number generate type to use.

Better random generators give better randomness (srsly!).
*/
typedef
fcppt::random::default_generator
random_generator;
}

#endif
