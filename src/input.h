#ifndef INPUT_H_
#define INPUT_H_

#include <SDL.h>
#include "structures/queue.h"

enum Key
{
	Up = SDL_CONTROLLER_BUTTON_DPAD_UP,
	Down = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
	Left = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
	Right = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
	Pause = SDL_CONTROLLER_BUTTON_START,
	Reset = SDL_CONTROLLER_BUTTON_BACK
};

typedef SDL_Event InputEvent;

class Input
{
	friend class Game;

public:
	~Input();

	// Returns a pointer to this singleton instance.
	static Input* instance();

	// Opens a controller if one is dectected.
	void initController();

	// Closes a controller if one is open.
	void closeController();

	// Returns true if a controller is connected.
	inline bool controller() const { return _controller ? true : false; }

	// Fills in the event with the next event in the queue if one exists.
	bool pollEvent(InputEvent* input);

	///////////////////////////////////////////////

	// Returns true if the specified keyboard key/controller button is down.
	static bool input(Key key);

private:
	Input();

	// Adds an SDL_Event to the event queue.
	void offerEvent(InputEvent e) { _events.offer(e); }

	// The connected controller.
	SDL_GameController* _controller = nullptr;

	// The event queue.
	Queue<SDL_Event> _events;

	// This singleton instance.
	static Input* _instance;

	///////////////////////////////////////////////

	/* Returns true if the specified controller button is down.
	static bool buttonDown(Key key);

	// Returns true if the specified keyboard key is down.
	static bool keyDown(Key key);

	// Returns true if the specified stick is in the specified direction.
	static bool joystick(Joystick stick, Direction direction);

	// Joystick deadzone.
	static constexpr Sint16 DEADZONE = 14000;*/
};

#endif
