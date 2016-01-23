#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ADAPTED_TYPES_RNG_SEED_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_ADAPTED_TYPES_RNG_SEED_HPP_INCLUDED

#include <sgeroids/model/serialization/message/types/rng_seed.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/serialization/endianness.hpp>


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
alda::bindings::unsigned_
<
	sgeroids::model::serialization::message::types::rng_seed,
	alda::serialization::endianness()
>
rng_seed;
}
}
}
}
}

#endif

