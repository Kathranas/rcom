#include "timer.hpp"

Timer::Timer() :
	running{},
	start_time{},
	accumulator{},
	lap_accumulator{},
	lap_count{}
{
}

void Timer::reset()
{
	running         = {};
	start_time      = {};
	accumulator     = {};
	lap_count       = {};
	lap_accumulator = {};
}

void Timer::start()
{
	if(is_running())
	{
		return;
	}

	start_time = Clock::now();
}

void Timer::stop()
{
	if(!is_running())
	{
		return;
	}

	accumulator += Clock::now() - start_time;
}

Timer::Duration Timer::lap()
{
	Duration lap_time = get_current_time();
	accumulator       = {};
	lap_accumulator   += lap_time;
	lap_count++;
	start_time        = Clock::now();
	return lap_time;
}

bool Timer::is_running() const
{
	return start_time > 0;
}

Timer::Duration Timer::get_lap_time() const
{
	if(is_running())
	{
		return accumulator + Clock::now() - start_time;
	}
	else
	{
		return accumulator;
	}
}

size_t Timer::get_lap_count() const
{
	return lap_count;
}

Timer::Duration Timer::get_average_time() const
{
	return lap_accumulator / lap_count;
}

Timer::Duration Timer::get_total_time() const
{
	return lap_accumulator + get_current_time();
}
