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

Sint16 Input::getInput(In input) const
{
	// The input is analogue.
	if(input > Right)
	{
		return SDL_GameControllerGetAxis(_controller,
			(SDL_GameControllerAxis)((input - Right) - 1));
	}

	return SDL_GameControllerGetButton(_controller,
		(SDL_GameControllerButton)input);
}

bool Input::pollEvent(InputEvent* e)
{
	if(_events.size() > 0)
	{
		*e = _events.poll();
		return true;
	}

	return false;
}

void Input::offerEvent(const SDL_Event& e)
{
	// Note: only controller events are currently supported.
	if(!_controller)
		return;

	InputEvent input;

	// A digital button was pressed.
	if(e.type == SDL_CONTROLLERBUTTONDOWN || e.type == SDL_CONTROLLERBUTTONUP)
	{
		if(e.cbutton.button > Right)
			return;

		input.input = (In)e.cbutton.button;
		input.state = e.type == SDL_CONTROLLERBUTTONDOWN ? 1 : 0;

		_events.offer(input);
		return;
	}

	// An analogue input was altered (stick or trigger).
	if(e.type == SDL_CONTROLLERAXISMOTION)
	{
		if(e.caxis.axis > (R2 - Right) - 1)
			return;

		input.input = (In)((e.caxis.axis + Right) + 1);
		input.state = e.caxis.value;

		_events.offer(input);
		return;
	}
}

Input* Input::_instance = nullptr;
