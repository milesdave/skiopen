#ifndef TIMER_H_
#define TIMER_H_

class Timer
{
public:
	Timer();

	~Timer();

	// Starts the timer.
	void start();

	// Stops the timer.
	void stop();

	// Pauses or unpauses the timer.
	void pause();

	// Returns the milliseconds since the timer started.
	int milliseconds() const;

	// Returns the seconds since the timer started.
	inline int seconds() const { return milliseconds() / 1000; }

	// Returns whether or not the timer has been started.
	inline bool started() const { return _isStarted; }

	// Returns whether or not the timer has been paused.
	inline bool paused() const { return _isPaused; }

private:
	// The time when the timer was started.
	int _startTime = 0;

	// The time when the timer was paused.
	int _pauseTime = 0;

	// Whether or not the timer has been started.
	bool _isStarted = false;

	// Whether or not the timer has been paused.
	bool _isPaused = false;
};

#endif
