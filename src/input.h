#ifndef INPUT_H_
#define INPUT_H_

#include <SDL_gamecontroller.h>
#include <SDL_scancode.h>

enum Key
{
	Up = SDL_CONTROLLER_BUTTON_DPAD_UP,
	Down = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
	Left = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
	Right = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
	Pause = SDL_CONTROLLER_BUTTON_START,
	Reset = SDL_CONTROLLER_BUTTON_BACK
};

enum Joystick
{
	JLeft,
	JRight
};

enum Direction
{
	DUp = Up,
	DDown = Down,
	DLeft = Left,
	DRight = Right
};

class Input
{
public:
	Input();

	~Input();

	// Opens a controller if one is dectected.
	static void initController();

	// Closes a controller if one is open.
	static void closeController();

	// Returns true if a controller is connected.
	static bool controller() { return _controller ? true : false; }

	// Returns true if the specified keyboard key/controller button is down.
	static bool input(Key key);

private:
	// Returns true if the specified controller button is down.
	static bool buttonDown(Key key);

	// Returns true if the specified keyboard key is down.
	static bool keyDown(Key key);

	// Returns true if the specified stick is in the specified direction.
	static bool joystick(Joystick stick, Direction direction);

	// The connected controller.
	static SDL_GameController* _controller;

	// Joystick deadzone.
	static constexpr Sint16 DEADZONE = 14000;
};

#endif
