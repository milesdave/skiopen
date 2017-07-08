#include "game.h"
#include "input.h"

#include <cstdio> // TODO

Input::Input() { }

Input::~Input()
{
	closeController();
}

Input* Input::instance()
{
	if(!_instance)
		_instance = new Input();
	return _instance;
}

void Input::initController()
{
	if(!SDL_IsGameController(0))
		return;

	_controller = SDL_GameControllerOpen(0);
	if(!_controller)
		Game::instance()->panic("SDL_GameControllerOpen()", SDL_GetError());

	printf("Controller connected!\n");
}

void Input::closeController()
{
	if(_controller)
	{
		SDL_GameControllerClose(_controller);
		_controller = nullptr;
		printf("Controller disconnected!\n");
	}
}

bool Input::pollEvent(InputEvent* input)
{
	if(_events.size() > 0)
	{
		*input = _events.poll();
		return true;
	}

	return false;
}

Input* Input::_instance = nullptr;

bool Input::input(Key key)
{
	/*if(_controller)
		return buttonDown(key);
	else
		return keyDown(key);*/

	return false;
}

/*bool Input::buttonDown(Key key)
{
	bool result = SDL_GameControllerGetButton(_controller,
		(SDL_GameControllerButton)key) ? true : false;

	// Directional key specified - try joystick as well.
	if((int)key >= (int)SDL_CONTROLLER_BUTTON_DPAD_UP && (int)key <= (int)SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
		result |= joystick(JLeft, (Direction)key);

	return result;
}

bool Input::keyDown(Key key)
{
	const Uint8* keyboard = SDL_GetKeyboardState(nullptr);

	switch(key)
	{
	case Up:
		if(keyboard[SDL_SCANCODE_UP] || keyboard[SDL_SCANCODE_W])
			return true;
		break;
	case Down:
		if(keyboard[SDL_SCANCODE_DOWN] || keyboard[SDL_SCANCODE_S])
			return true;
		break;
	case Left:
		if(keyboard[SDL_SCANCODE_LEFT] || keyboard[SDL_SCANCODE_A])
			return true;
		break;
	case Right:
		if(keyboard[SDL_SCANCODE_RIGHT] || keyboard[SDL_SCANCODE_D])
			return true;
		break;
	case Pause:
		if(keyboard[SDL_SCANCODE_F3])
			return true;
		break;
	case Reset:
		if(keyboard[SDL_SCANCODE_F2])
			return true;
		break;
	}

	return false;
}

bool Input::joystick(Joystick stick, Direction direction)
{
	Sint16 x, y;

	switch(stick)
	{
	case JLeft:
		x = SDL_GameControllerGetAxis(_controller, SDL_CONTROLLER_AXIS_LEFTX);
		y = SDL_GameControllerGetAxis(_controller, SDL_CONTROLLER_AXIS_LEFTY);
		break;
	case JRight:
		x = SDL_GameControllerGetAxis(_controller, SDL_CONTROLLER_AXIS_RIGHTX);
		y = SDL_GameControllerGetAxis(_controller, SDL_CONTROLLER_AXIS_RIGHTY);
		break;
	}

	switch(direction)
	{
	case DUp:
		if(y < -DEADZONE)
			return true;
		break;
	case DDown:
		if(y > DEADZONE)
			return true;
		break;
	case DLeft:
		if(x < -DEADZONE)
			return true;
		break;
	case DRight:
		if(x > DEADZONE)
			return true;
		break;
	}

	return false;
}*/
