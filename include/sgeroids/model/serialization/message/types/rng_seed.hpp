#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_TYPES_RNG_SEED_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_TYPES_RNG_SEED_HPP_INCLUDED

#include <sgeroids/random_generator.hpp>


namespace sgeroids
{
namespace model
{
namespace serialization
{
namespace message
{
namespace types
{
// TODO: Is this portable?
typedef sgeroids::random_generator::seed::value_type rng_seed;
}
}
}
}
}

#endif

