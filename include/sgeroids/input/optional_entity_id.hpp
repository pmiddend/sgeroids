#ifndef SGEROIDS_INPUT_OPTIONAL_ENTITY_ID_HPP_INCLUDED
#define SGEROIDS_INPUT_OPTIONAL_ENTITY_ID_HPP_INCLUDED

#include <sgeroids/model/entity_id.hpp>
#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sgeroids
{
namespace input
{
FCPPT_MAKE_STRONG_TYPEDEF(
	fcppt::optional::object<model::entity_id>,
	optional_entity_id);
}
}

#endif
