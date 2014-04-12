#ifndef SGEROIDS_REPLAY_FILE_READER_HPP_INCLUDED
#define SGEROIDS_REPLAY_FILE_READER_HPP_INCLUDED

#include <sgeroids/model/base_fwd.hpp>
#include <sgeroids/replay/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
namespace replay
{
class file_reader
{
FCPPT_NONCOPYABLE(
	file_reader);
public:
	file_reader(
		sgeroids::model::base &,
		boost::filesystem::path const &);

	void
	update();

	~file_reader();
private:
	boost::filesystem::ifstream input_stream_;
	std::unique_ptr<sgeroids::replay::object> replay_;
};
}
}

#endif

