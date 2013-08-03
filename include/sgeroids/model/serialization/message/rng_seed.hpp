#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_RNG_SEED_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_RNG_SEED_HPP_INCLUDED

#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/model/serialization/message/adapted_types/rng_seed.hpp>
#include <sgeroids/model/serialization/message/roles/seed.hpp>
#include <alda/message/make_class.hpp>
#include <alda/message/make_id.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace model
{
namespace serialization
{
namespace message
{
typedef
alda::message::make_class
<
	majutsu::composite
	<
		boost::mpl::vector2
		<
			alda::message::make_id
			<
				sgeroids::model::serialization::message::adapted_types::message,
				sgeroids::model::serialization::message::types::message::rng_seed
			>,
			majutsu::role
			<
				sgeroids::model::serialization::message::adapted_types::rng_seed,
				sgeroids::model::serialization::message::roles::seed
			>
		>
	>
>
rng_seed;
}
}
}
}

#endif

