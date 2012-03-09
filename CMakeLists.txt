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

namespace sgeroids
{
inline fcppt::string const
build_version()
{
	return
		FCPPT_TEXT(\"@SGEROIDS_VERSION@\");
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
find_package(
	Boost 1.45.0 REQUIRED COMPONENTS
	system)

include_directories(
	${Boost_INCLUDE_DIR})
link_directories(
	${Boost_LIBRARY_DIRS})

# boost-1.48 is broken with fusion, workaround
if(
	MSVC AND ${Boost_VERSION} STREQUAL "104800")
	add_definitions(
		-D BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
endif()
# boost end

# fcppt begin
find_package(
	Fcppt REQUIRED)
include_directories(
	${Fcppt_INCLUDE_DIRS})
add_definitions(
	${Fcppt_DEFINITIONS})
# fcppt end

# sge begin
find_package(
	SGE REQUIRED COMPONENTS
	audio
	charconv
	image
	image2d
	input
	core
	renderer
	sprite
	texture
	parse
	systems
	window
	viewport)

include_directories(
	${SGE_INCLUDE_DIRS})
add_definitions(
	${SGE_DEFINITIONS})
# sge end

# Get rid of a pretty useless warning
if(CMAKE_COMPILER_IS_GNUCXX OR FCPPT_UTILS_COMPILER_IS_CLANGPP)
	add_definitions(
		-Wno-old-style-cast)
endif()

# Begin media path stuff
# TODO: How exactly does this path stuff work?
set(
	INSTALL_MEDIA_DIR
	${INSTALL_DATA_DIR}/media)

include(
	SGECustomPath)

sge_config_add_custom_path(
	${CMAKE_PROJECT_NAME}
	media
	${CMAKE_SOURCE_DIR}/media
	${INSTALL_MEDIA_DIR})
# end media path stuff

# We don't want relative includes a la: #include "../foo/bar", so we partition
# the source into src/ and include/ and add include/ to the include
# directories
include_directories(
	${CMAKE_SOURCE_DIR}/include)

# Add ALL the source files here!
set(
	SGEROIDS_FILES
	src/sgeroids/exception.cpp
	src/sgeroids/input/keyboard.cpp
	src/sgeroids/input/log.cpp
	src/sgeroids/input/manager.cpp
	src/sgeroids/log.cpp
	src/sgeroids/log_context.cpp
	src/sgeroids/log_location.cpp
	src/sgeroids/log_parameters.cpp
	src/sgeroids/main.cpp
	src/sgeroids/math/discrete_cos.cpp
	src/sgeroids/math/discrete_sin.cpp
	src/sgeroids/math/unit_magnitude.cpp
	src/sgeroids/media_path.cpp
	src/sgeroids/model/base.cpp
	src/sgeroids/model/local/asteroid_generator/object.cpp
	src/sgeroids/model/local/entity/asteroid.cpp
	src/sgeroids/model/local/entity/base.cpp
	src/sgeroids/model/local/entity/projectile.cpp
	src/sgeroids/model/local/entity/spaceship.cpp
	src/sgeroids/model/local/object.cpp
	src/sgeroids/model/log.cpp
	src/sgeroids/random_generator_seed.cpp
	src/sgeroids/resource_tree/path.cpp
	src/sgeroids/resource_tree/strip_file_extension.cpp
	src/sgeroids/resource_tree/strip_path_prefix.cpp
	src/sgeroids/scoped_frame_limiter.cpp
	src/sgeroids/state_machine/object.cpp
	src/sgeroids/state_machine/states/ingame/superstate.cpp
	src/sgeroids/utf8_file_to_fcppt_string.cpp
	src/sgeroids/version.cpp
	src/sgeroids/view/base.cpp
	src/sgeroids/view/log.cpp
	src/sgeroids/view/planar/background/object.cpp
	src/sgeroids/view/planar/entity/asteroid.cpp
	src/sgeroids/view/planar/entity/base.cpp
	src/sgeroids/view/planar/entity/bullet.cpp
	src/sgeroids/view/planar/entity/spaceship.cpp
	src/sgeroids/view/planar/object.cpp
	src/sgeroids/view/planar/particle/object.cpp
	src/sgeroids/view/planar/radius_to_screen_space.cpp
	src/sgeroids/view/planar/rotation_to_screen_space.cpp
	src/sgeroids/view/planar/sprite_size_from_texture_and_radius.cpp
)

# Source groups are a MSVC file
fcppt_utils_add_source_groups(
	"${SGEROIDS_FILES}")

include(
	AwlMainGenerator)

# Executable
awl_utils_add_portable_executable(
	${CMAKE_PROJECT_NAME}
	"sgeroids::main"
	${SGEROIDS_FILES})

# Link to what?
target_link_libraries(
	${CMAKE_PROJECT_NAME}
	${Fcppt_core_LIBRARIES}
	${Fcppt_filesystem_LIBRARIES}
	${Awl_LIBRARIES}
	${SGE_LIBRARIES}
	${Boost_LIBRARIES})

install(
	TARGETS
	${CMAKE_PROJECT_NAME}
	DESTINATION
	${INSTALL_BINARY_DIR})

# doc begin
option(
	ENABLE_DOC
	"Build the documentation"
	OFF)

if(
	ENABLE_DOC)
	add_subdirectory(
		doc)
endif()
# doc end
