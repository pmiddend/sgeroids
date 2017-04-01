cmake_minimum_required(
	VERSION
	2.8.12
)

project(
	sgeroids)

find_package(
	fcppt REQUIRED)

include(
	FcpptCMakeUtils)

# Versioning stuff begin
set(SGEROIDS_MAJOR_VERSION 0)
set(SGEROIDS_MINOR_VERSION 1)
set(SGEROIDS_MICRO_VERSION 0)

set(
	SGEROIDS_VERSION
	"${SGEROIDS_MAJOR_VERSION}.${SGEROIDS_MINOR_VERSION}.${SGEROIDS_MICRO_VERSION}")

set(
	SGEROIDS_CONFIG_INCLUDE_DIR
	${CMAKE_BINARY_DIR}/sgeroidsconfig/include)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/version.hpp.in
	${SGEROIDS_CONFIG_INCLUDE_DIR}/sgeroids/build/version.hpp)

include_directories(
	${SGEROIDS_CONFIG_INCLUDE_DIR})
# Versioning stuff end

# Boost begin
find_package(
	Boost 1.47.0 REQUIRED COMPONENTS
	filesystem
	system)

find_package(
	awl REQUIRED)

find_package(
	mizuiro
	REQUIRED
)

find_package(
	sge REQUIRED
	COMPONENTS
	audio
	charconv
	config
	font
	fontdraw
	imagecolor
	image2d
	input
	core
	renderer
	sprite
	texture
	parsejson
	resource_tree
	systems
	timer
	window
	viewport
)

find_package(
	alda REQUIRED)

include(
	GNUInstallDirs)

# Begin media path stuff
# TODO: How exactly does this path stuff work?
set(
	INSTALL_MEDIA_DIR
	${FCPPT_UTILS_INSTALL_DATA_DIR}/media)

include(
	SGECustomPath)

sge_config_add_custom_path(
	${CMAKE_PROJECT_NAME}
	media
	${CMAKE_SOURCE_DIR}/media
	${CMAKE_INSTALL_PREFIX}/${INSTALL_MEDIA_DIR}
	MEDIA_PATH_INCLUDES
)
# end media path stuff

# We don't want relative includes a la: #include "../foo/bar", so we partition
# the source into src/ and include/ and add include/ to the include
# directories
include_directories(
	${CMAKE_SOURCE_DIR}/include)

# Add ALL the source files here!
set(
	SGEROIDS_FILES
	include/sgeroids/app_name.hpp
	include/sgeroids/exception.hpp
	include/sgeroids/input/keyboard.hpp
	include/sgeroids/input/keyboard_fwd.hpp
	include/sgeroids/input/manager.hpp
	include/sgeroids/input/optional_entity_id.hpp
	include/sgeroids/log_location.hpp
	include/sgeroids/log_parameters.hpp
	include/sgeroids/main.hpp
	include/sgeroids/math/degrees.hpp
	include/sgeroids/math/discrete_cos.hpp
	include/sgeroids/math/discrete_sin.hpp
	include/sgeroids/math/positive_mod.hpp
	include/sgeroids/math/unit_magnitude.hpp
	include/sgeroids/math/wrap_point_in_torus.hpp
	include/sgeroids/media_path.hpp
	include/sgeroids/model/asteroid_id.hpp
	include/sgeroids/model/base.hpp
	include/sgeroids/model/base_fwd.hpp
	include/sgeroids/model/callbacks/add_asteroid.hpp
	include/sgeroids/model/callbacks/add_asteroid_function.hpp
	include/sgeroids/model/callbacks/add_projectile.hpp
	include/sgeroids/model/callbacks/add_projectile_function.hpp
	include/sgeroids/model/callbacks/add_spaceship.hpp
	include/sgeroids/model/callbacks/add_spaceship_function.hpp
	include/sgeroids/model/callbacks/change_thrust.hpp
	include/sgeroids/model/callbacks/change_thrust_function.hpp
	include/sgeroids/model/callbacks/collide_projectile_asteroid.hpp
	include/sgeroids/model/callbacks/collide_projectile_asteroid_function.hpp
	include/sgeroids/model/callbacks/destroy_asteroid.hpp
	include/sgeroids/model/callbacks/destroy_asteroid_function.hpp
	include/sgeroids/model/callbacks/error.hpp
	include/sgeroids/model/callbacks/error_function.hpp
	include/sgeroids/model/callbacks/gameover.hpp
	include/sgeroids/model/callbacks/gameover_function.hpp
	include/sgeroids/model/callbacks/position_entity.hpp
	include/sgeroids/model/callbacks/position_entity_function.hpp
	include/sgeroids/model/callbacks/remove_entity.hpp
	include/sgeroids/model/callbacks/remove_entity_function.hpp
	include/sgeroids/model/callbacks/remove_spaceship.hpp
	include/sgeroids/model/callbacks/remove_spaceship_function.hpp
	include/sgeroids/model/callbacks/rotation_entity.hpp
	include/sgeroids/model/callbacks/rotation_entity_function.hpp
	include/sgeroids/model/callbacks/score_change.hpp
	include/sgeroids/model/callbacks/score_change_function.hpp
	include/sgeroids/model/dim2.hpp
	include/sgeroids/model/entity_id.hpp
	include/sgeroids/model/error_code.hpp
	include/sgeroids/model/error_code_fwd.hpp
	include/sgeroids/model/firing_mode.hpp
	include/sgeroids/model/firing_mode_fwd.hpp
	include/sgeroids/model/local/asteroid_generator/object.hpp
	include/sgeroids/model/local/asteroid_generator/object_fwd.hpp
	include/sgeroids/model/local/asteroid_generator/play_area_side.hpp
	include/sgeroids/model/local/asteroid_generator/play_area_side_fwd.hpp
	include/sgeroids/model/local/callbacks/asteroid_died.hpp
	include/sgeroids/model/local/callbacks/asteroid_died_function.hpp
	include/sgeroids/model/local/callbacks/asteroid_generation.hpp
	include/sgeroids/model/local/callbacks/asteroid_generation_function.hpp
	include/sgeroids/model/local/callbacks/increase_score.hpp
	include/sgeroids/model/local/callbacks/increase_score_function.hpp
	include/sgeroids/model/local/callbacks/insert_projectile.hpp
	include/sgeroids/model/local/callbacks/insert_projectile_function.hpp
	include/sgeroids/model/local/callbacks/position_entity_no_id.hpp
	include/sgeroids/model/local/callbacks/position_entity_no_id_function.hpp
	include/sgeroids/model/local/callbacks/rotation_entity_no_id.hpp
	include/sgeroids/model/local/callbacks/rotation_entity_no_id_function.hpp
	include/sgeroids/model/local/entity/asteroid.hpp
	include/sgeroids/model/local/entity/asteroid_fwd.hpp
	include/sgeroids/model/local/entity/base.hpp
	include/sgeroids/model/local/entity/base_fwd.hpp
	include/sgeroids/model/local/entity/projectile.hpp
	include/sgeroids/model/local/entity/spaceship.hpp
	include/sgeroids/model/local/entity/spaceship_fwd.hpp
	include/sgeroids/model/local/entity/unique_base_ptr.hpp
	include/sgeroids/model/local/error_context.hpp
	include/sgeroids/model/local/object.hpp
	include/sgeroids/model/play_area.hpp
	include/sgeroids/model/player_name.hpp
	include/sgeroids/model/position.hpp
	include/sgeroids/model/projectile_id.hpp
	include/sgeroids/model/radius.hpp
	include/sgeroids/model/rect.hpp
	include/sgeroids/model/rotation.hpp
	include/sgeroids/model/rotation_direction.hpp
	include/sgeroids/model/score.hpp
	include/sgeroids/model/serialization/context.hpp
	include/sgeroids/model/serialization/deserializer.hpp
	include/sgeroids/model/serialization/deserializer_fwd.hpp
	include/sgeroids/model/serialization/global_context.hpp
	include/sgeroids/model/serialization/message/adapted_types/char_type.hpp
	include/sgeroids/model/serialization/message/adapted_types/entity_id.hpp
	include/sgeroids/model/serialization/message/adapted_types/enum.hpp
	include/sgeroids/model/serialization/message/adapted_types/int.hpp
	include/sgeroids/model/serialization/message/adapted_types/message.hpp
	include/sgeroids/model/serialization/message/adapted_types/rng_seed.hpp
	include/sgeroids/model/serialization/message/adapted_types/string.hpp
	include/sgeroids/model/serialization/message/add_player.hpp
	include/sgeroids/model/serialization/message/all_messages.hpp
	include/sgeroids/model/serialization/message/base.hpp
	include/sgeroids/model/serialization/message/base_unique_ptr.hpp
	include/sgeroids/model/serialization/message/change_firing_mode.hpp
	include/sgeroids/model/serialization/message/change_thrust.hpp
	include/sgeroids/model/serialization/message/remove_player.hpp
	include/sgeroids/model/serialization/message/rng_seed.hpp
	include/sgeroids/model/serialization/message/roles/entity_id.hpp
	include/sgeroids/model/serialization/message/roles/firing_mode.hpp
	include/sgeroids/model/serialization/message/roles/player_name.hpp
	include/sgeroids/model/serialization/message/roles/rotation_direction.hpp
	include/sgeroids/model/serialization/message/roles/seed.hpp
	include/sgeroids/model/serialization/message/roles/thrust.hpp
	include/sgeroids/model/serialization/message/rotation_direction.hpp
	include/sgeroids/model/serialization/message/types/char_type.hpp
	include/sgeroids/model/serialization/message/types/entity_id.hpp
	include/sgeroids/model/serialization/message/types/enum.hpp
	include/sgeroids/model/serialization/message/types/int.hpp
	include/sgeroids/model/serialization/message/types/message.hpp
	include/sgeroids/model/serialization/message/types/message_fwd.hpp
	include/sgeroids/model/serialization/message/types/rng_seed.hpp
	include/sgeroids/model/serialization/message/types/string.hpp
	include/sgeroids/model/serialization/message/update.hpp
	include/sgeroids/model/spaceship_id.hpp
	include/sgeroids/model/thrust.hpp
	include/sgeroids/model/unique_base_ptr.hpp
	include/sgeroids/model/vector2.hpp
	include/sgeroids/model/velocity.hpp
	include/sgeroids/random_generator.hpp
	include/sgeroids/random_generator_fwd.hpp
	include/sgeroids/random_generator_seed.hpp
	include/sgeroids/replay/call_object.hpp
	include/sgeroids/replay/dispatcher.hpp
	include/sgeroids/replay/dispatcher_fwd.hpp
	include/sgeroids/replay/file_reader.hpp
	include/sgeroids/replay/file_reader_fwd.hpp
	include/sgeroids/replay/object.hpp
	include/sgeroids/replay/object_fwd.hpp
	include/sgeroids/resource_tree/instantiate_object.hpp
	include/sgeroids/resource_tree/object_decl.hpp
	include/sgeroids/resource_tree/object_fwd.hpp
	include/sgeroids/state_machine/events/render.hpp
	include/sgeroids/state_machine/events/tick.hpp
	include/sgeroids/state_machine/object.hpp
	include/sgeroids/state_machine/states/ingame/superstate.hpp
	include/sgeroids/state_machine/states/ingame/superstate_fwd.hpp
	include/sgeroids/systems.hpp
	include/sgeroids/systems_fwd.hpp
	include/sgeroids/version.hpp
	include/sgeroids/view/base.hpp
	include/sgeroids/view/base_fwd.hpp
	include/sgeroids/view/planar/audio_buffer_tree.hpp
	include/sgeroids/view/planar/audio_buffer_tree_fwd.hpp
	include/sgeroids/view/planar/background/object.hpp
	include/sgeroids/view/planar/background/star_count.hpp
	include/sgeroids/view/planar/background/star_size.hpp
	include/sgeroids/view/planar/callbacks/add_particle.hpp
	include/sgeroids/view/planar/callbacks/add_particle_function.hpp
	include/sgeroids/view/planar/entity/asteroid.hpp
	include/sgeroids/view/planar/entity/base.hpp
	include/sgeroids/view/planar/entity/base_fwd.hpp
	include/sgeroids/view/planar/entity/bullet.hpp
	include/sgeroids/view/planar/entity/spaceship.hpp
	include/sgeroids/view/planar/error_context.hpp
	include/sgeroids/view/planar/object.hpp
	include/sgeroids/view/planar/particle/lifespan.hpp
	include/sgeroids/view/planar/particle/object.hpp
	include/sgeroids/view/planar/particle/velocity.hpp
	include/sgeroids/view/planar/player_name.hpp
	include/sgeroids/view/planar/position.hpp
	include/sgeroids/view/planar/radius.hpp
	include/sgeroids/view/planar/radius_to_screen_space.hpp
	include/sgeroids/view/planar/rotation.hpp
	include/sgeroids/view/planar/rotation_to_screen_space.hpp
	include/sgeroids/view/planar/sprite/choices.hpp
	include/sgeroids/view/planar/sprite/color_format.hpp
	include/sgeroids/view/planar/sprite/dim.hpp
	include/sgeroids/view/planar/sprite/dynamic_buffers.hpp
	include/sgeroids/view/planar/sprite/object.hpp
	include/sgeroids/view/planar/sprite/order.hpp
	include/sgeroids/view/planar/sprite/ordered_collection.hpp
	include/sgeroids/view/planar/sprite/static_buffers.hpp
	include/sgeroids/view/planar/sprite/static_range.hpp
	include/sgeroids/view/planar/sprite/type_choices.hpp
	include/sgeroids/view/planar/sprite_size_from_texture_and_radius.hpp
	include/sgeroids/view/planar/texture_tree.hpp
	include/sgeroids/view/planar/texture_tree_fwd.hpp
	include/sgeroids/view/planar/vector2.hpp
	include/sgeroids/view/unique_base_ptr.hpp
	src/sgeroids/app_name.cpp
	src/sgeroids/exception.cpp
	src/sgeroids/input/keyboard.cpp
	src/sgeroids/input/manager.cpp
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
	src/sgeroids/model/serialization/global_context.cpp
	src/sgeroids/model/serialization/message/add_player.cpp
	src/sgeroids/model/serialization/message/base.cpp
	src/sgeroids/model/serialization/message/change_firing_mode.cpp
	src/sgeroids/model/serialization/message/change_thrust.cpp
	src/sgeroids/model/serialization/message/remove_player.cpp
	src/sgeroids/model/serialization/message/rng_seed.cpp
	src/sgeroids/model/serialization/message/rotation_direction.cpp
	src/sgeroids/model/serialization/message/type_enum_wrapper.cpp
	src/sgeroids/model/serialization/message/update.cpp
	src/sgeroids/random_generator_seed.cpp
	src/sgeroids/replay/dispatcher.cpp
	src/sgeroids/replay/file_reader.cpp
	src/sgeroids/replay/object.cpp
	src/sgeroids/state_machine/events/render.cpp
	src/sgeroids/state_machine/object.cpp
	src/sgeroids/state_machine/states/ingame/superstate.cpp
	src/sgeroids/version.cpp
	src/sgeroids/view/base.cpp
	src/sgeroids/view/planar/audio_buffer_tree.cpp
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
	src/sgeroids/view/planar/texture_tree.cpp
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

fcppt_utils_set_target_compiler_flags(
	${CMAKE_PROJECT_NAME}
)

target_include_directories(
	${CMAKE_PROJECT_NAME}
	PRIVATE
	${MEDIA_PATH_INCLUDES}
)

# Link to what?
target_link_libraries(
	${CMAKE_PROJECT_NAME}
	${fcppt_core_TARGET}
	${fcppt_filesystem_TARGET}
	${fcppt_log_TARGET}
	${awl_TARGET}
	${sge_TARGETS}
	${alda_TARGET}
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEMS_LIBRARY}
)

install(
	TARGETS
	${CMAKE_PROJECT_NAME}
	DESTINATION
	${CMAKE_INSTALL_BINDIR})

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
