#ifndef SGEROIDS_SYSTEMS_FWD_HPP_INCLUDED
#define SGEROIDS_SYSTEMS_FWD_HPP_INCLUDED

#include <sge/systems/keyboard_collector_fwd.hpp>
#include <sge/systems/instance_fwd.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/with_audio_loader_fwd.hpp>
#include <sge/systems/with_audio_player_fwd.hpp>
#include <sge/systems/with_font_fwd.hpp>
#include <sge/systems/with_image2d_fwd.hpp>
#include <sge/systems/with_input_fwd.hpp>
#include <sge/systems/with_renderer_fwd.hpp>
#include <sge/systems/with_window_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{

typedef sge::systems::instance<
	boost::mpl::vector7<
		sge::systems::with_window,
		sge::systems::with_renderer<
			sge::systems::renderer_caps::ffp
		>,
		sge::systems::with_input<
			boost::mpl::vector1<
				sge::systems::keyboard_collector
			>
		>,
		sge::systems::with_image2d,
		sge::systems::with_font,
		sge::systems::with_audio_loader,
		sge::systems::with_audio_player
	>
> systems;

}

#endif
