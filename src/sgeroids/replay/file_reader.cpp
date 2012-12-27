#include <sgeroids/replay/file_reader.hpp>
#include <sgeroids/replay/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/pre.hpp>


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

	replay_.take(
		fcppt::make_unique_ptr<sgeroids::replay::object>(
			_model,
			input_stream_));
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
