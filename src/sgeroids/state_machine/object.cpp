#include <sgeroids/exception.hpp>
#include <sgeroids/media_path.hpp>
#include <sgeroids/systems.hpp>
#include <sgeroids/version.hpp>
#include <sgeroids/state_machine/object.hpp>
#include <sgeroids/state_machine/events/render.hpp>
#include <sgeroids/state_machine/events/tick.hpp>
#include <sge/charconv/utf8_file_to_fcppt_string_exn.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/parse/json/convert_from.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <sge/parse/json/parse_string_exn.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/config/create_command_line_parameters.hpp>
#include <sge/parse/json/config/merge_command_line_parameters.hpp>
#include <sge/parse/json/config/merge_trees.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/multi_samples.hpp>
#include <sge/renderer/pixel_format/multi_samples_value.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/timer/scoped_frame_limiter.hpp>
#include <sge/viewport/fractional_aspect.hpp>
#include <sge/viewport/maintain_aspect.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_success.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/variant/holds_type.hpp>


namespace
{
// This helper function takes config file parameters and creates renderer
// parameters from it.
sge::systems::renderer
renderer_parameters_from_config_file(
	sge::parse::json::object const &_config)
{
	sge::renderer::display_mode::vsync const vsync_enabled =
		sge::parse::json::find_and_convert_member<bool>(
			_config,
			sge::parse::json::path(FCPPT_TEXT("renderer")) / FCPPT_TEXT("vsync-enabled"))
		?
			sge::renderer::display_mode::vsync::on
		:
			sge::renderer::display_mode::vsync::off;

	sge::parse::json::value const &multi_sampling_json =
		sge::parse::json::find_and_convert_member<sge::parse::json::value>(
			_config,
			sge::parse::json::path(FCPPT_TEXT("renderer")) / FCPPT_TEXT("multi-sample-type"));

	sge::renderer::pixel_format::optional_multi_samples multi_sampling_sge;

	if(!fcppt::variant::holds_type<sge::parse::json::null>(multi_sampling_json))
		multi_sampling_sge =
			sge::renderer::pixel_format::optional_multi_samples(
				sge::renderer::pixel_format::multi_samples(
					sge::parse::json::convert_from<sge::renderer::pixel_format::multi_samples_value>(
						multi_sampling_json)));

	unsigned const bit_depth_value =
		sge::parse::json::find_and_convert_member<unsigned>(
			_config,
			sge::parse::json::path(FCPPT_TEXT("renderer")) / FCPPT_TEXT("visual-depth"));

	sge::renderer::pixel_format::color const
		bit_depth_sge =
			bit_depth_value == 16
			?
				sge::renderer::pixel_format::color::depth16
			:
				(bit_depth_value == 32
				?
					sge::renderer::pixel_format::color::depth32
				:
					throw
						sgeroids::exception(
							FCPPT_TEXT("Unknown visual depth value encountered: ")+
							fcppt::insert_to_fcppt_string(
								bit_depth_value)));

	return
		sge::systems::renderer(
			sge::renderer::pixel_format::object(
				bit_depth_sge,
				sge::renderer::pixel_format::depth_stencil::off,
				multi_sampling_sge,
				sge::renderer::pixel_format::srgb::no
			),
			sge::renderer::display_mode::parameters(
				vsync_enabled,
				sge::renderer::display_mode::optional_object()
			),
			sge::viewport::optional_resize_callback{
				sge::viewport::maintain_aspect(
					sge::viewport::fractional_aspect(
						1u,
						1u
					)
				)
			}
		);
}
}

sgeroids::state_machine::object::object(
	int const _argc,
	char * _argv[])
:
	config_(
		sge::parse::json::config::merge_command_line_parameters(
			sge::parse::json::parse_string_exn(
				sge::charconv::utf8_file_to_fcppt_string_exn(
					sgeroids::media_path()/FCPPT_TEXT("config.json"))).object(),
			sge::parse::json::config::create_command_line_parameters(
				_argc,
				_argv))),
	systems_(
		sge::systems::make_list(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sgeroids-")
							+
							sgeroids::version()
						)
					)
					.dim(
						sge::parse::json::find_and_convert_member<
							sge::window::dim
						>(
							this->config(),
							sge::parse::json::path(
								FCPPT_TEXT("renderer")
							)
							/
							FCPPT_TEXT("window-size")
						)
					)
				)
			)
		)(
			renderer_parameters_from_config_file(
				this->config()
			)
		)(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)(
			sge::systems::audio_player_default()
		)(
			sge::systems::font()
		)(
			sge::systems::image2d(
				sge::media::optional_extension_set(
					sge::media::extension_set{
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					}
				)
			)
		)(
			sge::systems::audio_loader(
				sge::media::optional_extension_set(
					sge::media::extension_set{
						sge::media::extension(
							FCPPT_TEXT("ogg")
						)
					}
				)
			)
		)
	)
{
}

sge::parse::json::object const &
sgeroids::state_machine::object::config() const
{
	return config_;
}

sgeroids::systems const &
sgeroids::state_machine::object::systems() const
{
	return systems_;
}

awl::main::exit_code const
sgeroids::state_machine::object::run()
{
	while(
		systems_.window_system().poll())
	{
		sge::timer::scoped_frame_limiter frame_limiter(
			60);

		this->process_event(
			sgeroids::state_machine::events::tick());

		sge::renderer::context::scoped_ffp const scoped_block(
			systems_.renderer_device_ffp(),
			systems_.renderer_device_ffp().onscreen_target());

		this->process_event(
			sgeroids::state_machine::events::render(
				scoped_block.get()));
	}

	return
		systems_.window_system().exit_code();
}

void
sgeroids::state_machine::object::exit_mainloop()
{
	systems_.window_system().quit(
		awl::main::exit_success());
}

sgeroids::state_machine::object::~object()
{
}
