#include "game.h"
#include "input.h"

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
}

void Input::closeController()
{
	if(_controller)
	{
		SDL_GameControllerClose(_controller);
		_controller = nullptr;
	}
}

bool Input::pollEvent(SDL_Event* e)
{
	if(_events.size() > 0)
	{
		*e = _events.poll();
		return true;
	}

	return false;
}

void Input::offerEvent(SDL_Event e)
{
	_events.offer(e);
}

Input::State Input::instant(InputType input) const
{
	if(_controller)
		return controllerInstant(input);

	return keyboardInstant(input);
}

Input::State Input::controllerInstant(InputType input) const
{
	Sint16 x = SDL_GameControllerGetAxis(_controller, SDL_CONTROLLER_AXIS_LEFTX);
	Sint16 y = SDL_GameControllerGetAxis(_controller, SDL_CONTROLLER_AXIS_LEFTY);

	switch(input)
	{
	case Up:
		if(y < -DEADZONE)
			return Pressed;
		else if(y < -DEADZONE_HALF)
			return Half;
		break;
	case Down:
		if(y > DEADZONE)
			return Pressed;
		else if(y > DEADZONE_HALF)
			return Half;
		break;
	case Left:
		if(x < -DEADZONE)
			return Pressed;
		else if(x < -DEADZONE_HALF)
			return Half;
		break;
	case Right:
		if(x > DEADZONE)
			return Pressed;
		else if(x > DEADZONE_HALF)
			return Half;
		break;
	}

	return Released;
}

Input::State Input::keyboardInstant(InputType input) const
{
	const Uint8* keyboard = SDL_GetKeyboardState(nullptr);

	switch(input)
	{
	case Up:
		if(keyboard[SDL_SCANCODE_UP] || keyboard[SDL_SCANCODE_W])
			return Pressed;
		break;
	case Down:
		if(keyboard[SDL_SCANCODE_DOWN] || keyboard[SDL_SCANCODE_S])
			return Pressed;
		break;
	case Left:
		if(keyboard[SDL_SCANCODE_LEFT] || keyboard[SDL_SCANCODE_A])
			return Pressed;
		break;
	case Right:
		if(keyboard[SDL_SCANCODE_RIGHT] || keyboard[SDL_SCANCODE_D])
			return Pressed;
		break;
	}

	return Released;
}

Input* Input::_instance = nullptr;
