#pragma once

#include <chrono>

class Timer
{
public:
	typedef std::chrono::duration<float, std::milli> Duration;

	         Timer();
	void     reset();
	void     start();
	void     stop();
	Duration lap();

	bool     is_running()       const;
	Duration get_lap_time()     const;
	size_t   get_lap_count()    const;
	Duration get_average_time() const;
	Duration get_total_time()   const;
private:
	typedef std::chrono::steady_clock   Clock;
	typedef time_point<Clock, Duration> TimePoint;

	TimePoint  start_time;
	Duration   accumulator;
	Duration   lap_accumulator;
	uint32_t   lap_count;
};
