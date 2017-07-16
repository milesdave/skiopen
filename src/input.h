#ifndef INPUT_H_
#define INPUT_H_

#include <SDL.h>
#include "structures/queue.h"
#include "types.h"

class Input
{
public:
	~Input();

	// The state of the InputType.
	enum State
	{
		Released = 0,
		Half = 1,
		Pressed = 2
	};

	// The types of input used in this game.
	enum InputType
	{
		Up,
		Down,
		Left,
		Right,
	};

	// Returns a pointer to this singleton instance.
	static Input* instance();

	// Opens a controller if one is dectected.
	void initController();

	// Closes a controller if one is open.
	void closeController();

	// Returns true if a controller is connected.
	inline bool controller() const { return _controller ? true : false; }

	// Returns the state of the specified input right now.
	State instant(InputType input) const;

	// Fills in the event with the next event in the Queue if one exists.
	bool pollEvent(SDL_Event* e);

	// Adds an SDL_Event to the Queue. Should only be used by the Game
	// class.
	void offerEvent(SDL_Event e);

private:
	Input();

	// Returns the state of the specified input on the controller.
	State controllerInstant(InputType input) const;

	// Returns the state of the specified input on the keyboard.
	State keyboardInstant(InputType input) const;

	// The connected controller.
	SDL_GameController* _controller = nullptr;

	// The event queue.
	Queue<SDL_Event> _events;

	// This singleton instance.
	static Input* _instance;

	// Controller analogue stick deadzones.
	static constexpr Sint16 DEADZONE = 22000;
	static constexpr Sint16 DEADZONE_HALF = 15000;
};

#endif
