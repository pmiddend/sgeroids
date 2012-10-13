#ifndef SGEROIDS_MODEL_PLAYER_NAME_HPP_INCLUDED
#define SGEROIDS_MODEL_PLAYER_NAME_HPP_INCLUDED

#include <sgeroids/model/serialization/message/types/string.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sgeroids
{
namespace model
{
FCPPT_MAKE_STRONG_TYPEDEF(
	sgeroids::model::serialization::message::types::string,
	player_name);
}
}

#endif
