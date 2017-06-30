#include <SDL.h>
#include "timer.h"

Timer::Timer() { }

Timer::~Timer() { }

void Timer::start()
{
	_startTime = SDL_GetTicks();
	_pauseTime = 0;

	_isStarted = true;
	_isPaused = false;
}

void Timer::stop()
{
	_startTime = 0;
	_pauseTime = 0;

	_isStarted = false;
	_isPaused = false;
}

void Timer::pause()
{
	// The timer is running, but not paused.
	if(_isStarted && !_isPaused)
	{
		_pauseTime = SDL_GetTicks() - _startTime;
		_startTime = 0;
		_isPaused = true;
	}
	// The timer is running and paused.
	else if(_isStarted && _isPaused)
	{
		_startTime = SDL_GetTicks() - _pauseTime;
		_pauseTime = 0;
		_isPaused = false;
	}
}

int Timer::getMilliseconds() const
{
	int time = 0;

	if(_isStarted)
	{
		if(_isPaused)
			time = _pauseTime;
		else
			time = SDL_GetTicks() - _startTime;
	}

	return time;
}
