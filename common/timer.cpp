#include "timer.h" 
Timer::Timer() 
{ 
	_seconds = 0;
	startSec = 0;
} 
Timer::~Timer() 
{ 
}

void Timer::StartTimer()
{
	startSec = _sec();
}

void Timer::StopTimer()
{
	_seconds = 0;
	startSec = 0;
}

float Timer::Seconds()
{
	_seconds = _sec() - startSec;
	return _seconds;
}

double Timer::_sec()
{
	return glfwGetTime();
}
