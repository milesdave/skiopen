#include <SDL.h>
#include "game.h"
#include "input.h"

Input::Input() { }

Input::~Input() { }

void Input::initController()
{
	if(SDL_NumJoysticks() < 1 || !SDL_IsGameController(0))
		return;

	_controller = SDL_GameControllerOpen(0);
	if(!_controller)
		Game::instance()->panic("SDL_GameControllerOpen()", SDL_GetError());
}

void Input::closeController()
{
	if(_controller)
		SDL_GameControllerClose(_controller);
}

bool Input::input(Key key)
{
	if(_controller)
		return buttonDown(key);
	else
		return keyDown(key);
}

bool Input::buttonDown(Key key)
{
	return false; // TODO (bool)SDL_GameControllerGetButton(_controller, (SDL_GameControllerButton)key);
}

bool Input::keyDown(Key key)
{
	return false; // TODO
}

SDL_GameController* Input::_controller = nullptr;
