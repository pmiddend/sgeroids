#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_UPDATE_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_UPDATE_HPP_INCLUDED

#include <alda/message/make_class.hpp>
#include <alda/message/make_id.hpp>
#include <majutsu/composite.hpp>
#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/model/serialization/message/types/message.hpp>
#include <boost/mpl/vector/vector10.hpp>

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
		boost::mpl::vector1
		<
			alda::message::make_id
			<
				sgeroids::model::serialization::message::adapted_types::message,
				sgeroids::model::serialization::message::types::message::update
			>::type
		>
	>
>::type
update;
}
}
}
}

#endif

