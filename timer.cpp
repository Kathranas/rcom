#include "timer.hpp"

rcom::Timer::Timer() :
	running{},
	start_time{},
	accumulator{},
	lap_accumulator{},
	lap_count{}
{
}

void rcom::Timer::reset()
{
	running         = {};
	start_time      = {};
	accumulator     = {};
	lap_count       = {};
	lap_accumulator = {};
}

void rcom::Timer::start()
{
	if(is_running())
	{
		return;
	}

	start_time = Clock::now();
}

void rcom::Timer::stop()
{
	if(!is_running())
	{
		return;
	}

	accumulator += Clock::now() - start_time;
}

rcom::Timer::Duration rcom::Timer::lap()
{
	Duration lap_time = get_current_time();
	accumulator       = {};
	lap_accumulator   += lap_time;
	lap_count++;
	start_time        = Clock::now();
	return lap_time;
}

bool rcom::Timer::is_running() const
{
	return start_time > 0;
}

rcom::Timer::Duration rcom::Timer::get_lap_time() const
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

size_t rcom::Timer::get_lap_count() const
{
	return lap_count;
}

rcom::Timer::Duration rcom::Timer::get_average_time() const
{
	return lap_accumulator / lap_count;
}

rcom::Timer::Duration rcom::Timer::get_total_time() const
{
	return lap_accumulator + get_current_time();
}
