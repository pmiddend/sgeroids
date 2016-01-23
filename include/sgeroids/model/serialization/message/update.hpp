#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_UPDATE_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_UPDATE_HPP_INCLUDED

#include <sgeroids/model/serialization/message/adapted_types/message.hpp>
#include <sgeroids/model/serialization/message/types/message.hpp>
#include <alda/message/record.hpp>
#include <alda/message/make_id.hpp>
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
alda::message::record
<
	alda::message::make_id
	<
		sgeroids::model::serialization::message::adapted_types::message,
		sgeroids::model::serialization::message::types::message::update
	>,
	boost::mpl::vector0
	<
	>
>
update;
}
}
}
}

#endif

