#ifndef SGEROIDS_SCOPED_FRAME_LIMITER_HPP_INCLUDED
#define SGEROIDS_SCOPED_FRAME_LIMITER_HPP_INCLUDED

#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/system_clocks.hpp>
#include <fcppt/config/external_end.hpp>


namespace sgeroids
{
/**
\brief Force a code block to execute at least a given number of milliseconds

This class is used to artificially limit the frame rate or the duration of one
simulation "tick" to a specified amount of milliseconds.
*/
class scoped_frame_limiter
{
FCPPT_NONCOPYABLE(
	scoped_frame_limiter);
public:
	typedef
	boost::chrono::high_resolution_clock
	clock_type;

	typedef
	clock_type::rep
	ticks_per_second;

	/**
	\brief Notes the current time for later comparison
	\param f Denotes the targeted number of ticks per seconds

	Any frame that's shorter than 1/f will be stalled (by calling sleep, so
	no CPU is consumed).
	*/
	explicit
	scoped_frame_limiter(
		ticks_per_second);

	/**
	\brief Compares the stored time with the current time and calls sleep
	*/
	~scoped_frame_limiter();
private:
	clock_type::time_point const before_frame_;
	clock_type::duration minimum_frame_length_;
};
}

#endif
