# 2.6 is more or less guesswork
cmake_minimum_required(VERSION 2.6)

project(
	sgeroids)

include(
	FcpptCMakeUtils)

# Versioning stuff begin
set(SGEROIDS_MAJOR_VERSION 0)
set(SGEROIDS_MINOR_VERSION 1)
set(SGEROIDS_MICRO_VERSION 0)

set(
	SGEROIDS_VERSION
	"${SGEROIDS_MAJOR_VERSION}.${SGEROIDS_MINOR_VERSION}.${SGEROIDS_MICRO_VERSION}")

file(
	WRITE
	${CMAKE_CURRENT_BINARY_DIR}/version.hpp.in
"
#ifndef SGEROIDS_BUILD_VERSION_HPP_INCLUDED
#define SGEROIDS_BUILD_VERSION_HPP_INCLUDED

#include <fcppt/text.hpp>
#include <fcppt/string.hpp>

#define SGEROIDS_CONFIG_TEXT_WRAPPER(\\
	text\\
)\\
	FCPPT_TEXT(\\
		text\\
	)

namespace sgeroids
{
inline fcppt::string const
build_version()
{
	return
		SGEROIDS_CONFIG_TEXT_WRAPPER(\"@SGEROIDS_VERSION\");
}
}

#endif
")

set(
	SGEROIDS_CONFIG_INCLUDE_DIR
	${CMAKE_BINARY_DIR}/sgeroidsconfig/include)

configure_file(
	${CMAKE_CURRENT_BINARY_DIR}/version.hpp.in
	${SGEROIDS_CONFIG_INCLUDE_DIR}/sgeroids/build/version.hpp)

include_directories(
	${SGEROIDS_CONFIG_INCLUDE_DIR})
# Versioning stuff end

# Boost begin
FIND_PACKAGE(
	Boost 1.45.0 REQUIRED COMPONENTS
	system)

INCLUDE_DIRECTORIES(
	${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(
	${Boost_LIBRARY_DIRS})

# boost-1.48 is broken with fusion, workaround
IF(
	MSVC AND ${Boost_VERSION} STREQUAL "104800")
	ADD_DEFINITIONS(
		-D BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
ENDIF()
# boost end

# fcppt begin
FIND_PACKAGE(
	Fcppt REQUIRED)
INCLUDE_DIRECTORIES(
	${Fcppt_INCLUDE_DIRS})
ADD_DEFINITIONS(
	${Fcppt_DEFINITIONS})
# fcppt end

# sge begin
FIND_PACKAGE(
	SGE REQUIRED COMPONENTS
	image
	image2d
	input
	renderer
	sprite
	texture
	parse
	systems
	window
	viewport)

INCLUDE_DIRECTORIES(
	${SGE_INCLUDE_DIRS})
ADD_DEFINITIONS(
	${SGE_DEFINITIONS})
# sge end

# Get rid of a pretty useless warning
IF(CMAKE_COMPILER_IS_GNUCXX OR FCPPT_UTILS_COMPILER_IS_CLANGPP)
	ADD_DEFINITIONS(
		-Wno-old-style-cast)
ENDIF()

# Begin media path stuff
# TODO: How exactly does this path stuff work?
SET(
	INSTALL_MEDIA_DIR
	${INSTALL_DATA_DIR}/media)

INCLUDE(
	SGECustomPath)

SGE_CONFIG_ADD_CUSTOM_PATH(
	${CMAKE_PROJECT_NAME}
	media
	${CMAKE_SOURCE_DIR}/media
	${INSTALL_MEDIA_DIR})
# end media path stuff

# We don't want relative includes a la: #include "../foo/bar", so we partition
# the source into src/ and include/ and add include/ to the include
# directories
INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/include)

# Add ALL the source files here!
SET(
	SGEROIDS_FILES
	src/sgeroids/exception.cpp
	src/sgeroids/log.cpp
	src/sgeroids/log_context.cpp
	src/sgeroids/main.cpp
	src/sgeroids/math/discrete_cos.cpp
	src/sgeroids/math/discrete_sin.cpp
	src/sgeroids/math/unit_magnitude.cpp
	src/sgeroids/media_path.cpp
	src/sgeroids/model/local/entity/base.cpp
	src/sgeroids/model/local/entity/spaceship.cpp
	src/sgeroids/model/local/object.cpp
	src/sgeroids/random_generator_seed.cpp
	src/sgeroids/resource_tree/path.cpp
	src/sgeroids/resource_tree/strip_file_extension.cpp
	src/sgeroids/resource_tree/strip_path_prefix.cpp
	src/sgeroids/state_machine/object.cpp
	src/sgeroids/state_machine/states/ingame/superstate.cpp
	src/sgeroids/utf8_file_to_fcppt_string.cpp
	src/sgeroids/version.cpp
	src/sgeroids/view/base.cpp
	src/sgeroids/view/log.cpp
	src/sgeroids/view/planar/entity/base.cpp
	src/sgeroids/view/planar/entity/spaceship.cpp
	src/sgeroids/view/planar/object.cpp
	src/sgeroids/view/planar/radius_to_screen_space.cpp
	src/sgeroids/view/planar/rotation_to_screen_space.cpp
	src/sgeroids/view/planar/sprite_size_from_texture_and_radius.cpp
)

# Source groups are a MSVC file
FCPPT_UTILS_ADD_SOURCE_GROUPS(
	"${SGEROIDS_FILES}")

# Executable
ADD_EXECUTABLE(
	${CMAKE_PROJECT_NAME}
	# Adding WIN32 is safe, it'll do nothing if we're on anything other
	# than Windows. On Windows, it'll force the creation of a
	# "non-console" application, which is what you want on Windows.
	WIN32
	${SGEROIDS_FILES})

# Link to what?
TARGET_LINK_LIBRARIES(
	${CMAKE_PROJECT_NAME}
	${Fcppt_core_LIBRARIES}
	${Fcppt_filesystem_LIBRARIES}
	${SGE_LIBRARIES}
	${Boost_LIBRARIES})

INSTALL(
	TARGETS
	${CMAKE_PROJECT_NAME}
	DESTINATION
	${INSTALL_BINARY_DIR})

# doc begin
OPTION(
	ENABLE_DOC
	"Build the documentation"
	OFF)

IF(
	ENABLE_DOC)
	ADD_SUBDIRECTORY(
		doc)
ENDIF()
# doc end
