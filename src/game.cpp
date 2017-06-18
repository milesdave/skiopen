#include <cstdlib>
#include <ctime>
#include "data.h"
#include "game.h"

Game::Game()
{
	if(!_instance)
		_instance = this;
}

Game::~Game()
{
	delete Data::instance();

	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Game::init()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
		panic("SDL_Init()", SDL_GetError());

	SDL_DisplayMode screenInfo;
	if((SDL_GetCurrentDisplayMode(0, &screenInfo)) != 0)
		panic("SDL_GetCurrentDisplayMode()", SDL_GetError());

	_winWidth = screenInfo.w / 2;
	_winHeight = screenInfo.h / 2;

	_window = SDL_CreateWindow("SkiOpen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _winWidth, _winHeight, SDL_WINDOW_SHOWN);
	if(!_window)
		panic("SDL_CreateWindow()", SDL_GetError());

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!_renderer)
		panic("SDL_CreateRenderer()", SDL_GetError());

	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);

	srand((unsigned)time(nullptr));

	Data::instance()->load();
	_camera.setGeometry(Rect { 0, 0, _winWidth, _winHeight });

	setup();
}

void Game::loop()
{
	int start, end, delay;

	while(!_quit)
	{
		start = SDL_GetTicks();

		handleInput();
		update();
		render();

		// Frame was too slow.
		end = SDL_GetTicks() - start;
		if(end >= (int)TIME_STEP || end < 0)
		{
			_deltaTime = (float)end / 1000.0f;
			continue;
		}

		// Frame was too fast.
		delay = TIME_STEP - end;
		if(delay > 0)
		{
			SDL_Delay(delay);
			_deltaTime = 1.0f / (float)FPS;
		}
	}
}

void Game::panic(const char* title, const char* message) const
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, _window);
	exit(1);
}

void Game::windowDimentions(int* width, int* height) const
{
	if(width)
		*width = _winWidth;
	if(height)
		*height = _winHeight;
}

GameObject* Game::createGameObject()
{
	GameObject *x = _gameObjects.allocate();
	*x = GameObject();
	return x;
}

void Game::setup()
{
	// TODO Add setup.
}

void Game::handleInput()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT:
			_quit = true;
			break;
		}
	}
}

void Game::update()
{
	for(int i = 0; i < _gameObjects.capacity(); i++)
	{
		if(_gameObjects[i])
		{
			_gameObjects[i]->update();

			// delete if neccissary
			if(_gameObjects[i]->getDeleteFlag())
			{
				_gameObjects.remove(i);
				continue;
			}

			// add to render list if neccissary
			if(_camera.onScreen(_gameObjects[i]->spritePosition()))
				_renderList.add(_gameObjects[i]);
		}
	}

	_camera.update();
}

void Game::render()
{
	SDL_RenderClear(_renderer);

	for(int i = 0; i < _renderList.size(); i++)
		_renderList[i]->render();
	_renderList.clear();

	SDL_RenderPresent(_renderer);
}

int Game::randomInRange(int min, int max)
{
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

Rect Game::centre(Rect original, Vector2 point)
{
	return Rect { point.x - (original.w / 2), point.y - (original.h / 2), original.w, original.h };
}

Game* Game::_instance = nullptr;
