#include "timer.h" 
Timer::Timer() 
{ 
	_seconds = 0;
	_start = false;
} 
Timer::~Timer() 
{ 
}

void Timer::update(float deltaTime)
{
	if (_start)
	{
		_seconds += deltaTime;
	}
}

void Timer::StartTimer()
{
	_start = true;
	_seconds = 0;
}

void Timer::TogglePause()
{
	_start = !_start;
}

void Timer::StopTimer()
{
	_start = false;
	_seconds = 0;
}
