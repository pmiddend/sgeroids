#ifndef SGEROIDS_CLOCK_HPP_INCLUDED
#define SGEROIDS_CLOCK_HPP_INCLUDED

namespace sgeroids
{
class clock
{
FCPPT_NONCOPYABLE(
	clock);
public:
	typedef
	int
	rep;

	typedef
	fcppt::ratio::nano
	period;

	typedef
	fcppt::chrono::duration
	<
		rep,
		period
	>
	duration;

	typedef
	fcppt::chrono::time_point
	<
		clock
	>
	time_point;

	static bool const is_steady = true;

	explicit
	clock();

	time_point
	now();
private:
	time_point current_;
};
}

#endif
