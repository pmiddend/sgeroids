#include <sgeroids/replay/file_reader.hpp>
#include <sgeroids/replay/object.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


sgeroids::replay::file_reader::file_reader(
	sgeroids::model::base &_model,
	boost::filesystem::path const &_path)
:
	input_stream_(
		_path),
	replay_()
{
	FCPPT_ASSERT_PRE(
		input_stream_.is_open());

	replay_ =
		std::make_unique<sgeroids::replay::object>(
			_model,
			input_stream_);
}

void
sgeroids::replay::file_reader::update()
{
	if(!replay_->done())
		replay_->update();
}

sgeroids::replay::file_reader::~file_reader()
{
}
