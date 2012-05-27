#ifndef SGEROIDS_MODEL_SERIALIZATION_MESSAGE_TYPES_CHAR_TYPE_HPP_INCLUDED
#define SGEROIDS_MODEL_SERIALIZATION_MESSAGE_TYPES_CHAR_TYPE_HPP_INCLUDED

#include <sge/charconv/char_type.hpp>
#include <sge/charconv/encoding.hpp>

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
typedef
sge::charconv::char_type
<
	sge::charconv::encoding::utf8
>::type
char_type;
}
}
}
}
}

#endif

