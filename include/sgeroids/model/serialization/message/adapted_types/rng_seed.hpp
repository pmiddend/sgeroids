#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ADAPTED_TYPES_RNG_SEED_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ADAPTED_TYPES_RNG_SEED_HPP_INCLUDED

#include <sgeroids/random_generator.hpp>
#include <alda/bindings/fundamental.hpp>


namespace sgeroids
{
namespace model
{
namespace serialization
{
namespace message
{
namespace adapted_types
{
typedef
alda::bindings::fundamental
<
	sgeroids::random_generator::seed::value_type
>
rng_seed;
}
}
}
}
}

#endif

