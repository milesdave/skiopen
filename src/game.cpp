#include <cstdlib>
#include <ctime>
#include "data.h"
#include "game.h"
#include "input.h"
#include "levels/mainlevel.h"

Game::Game()
{
	if(!_instance)
		_instance = this;
}

Game::~Game()
{
	Input::closeController();
	delete Data::instance();

	for(int i = 0; i < LEVELS; i++)
		delete _levels[i];

	if(_quadtree)
		delete _quadtree;

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

	_winWidth = (int)(screenInfo.w * 0.5f);
	_winHeight = (int)(screenInfo.h * 0.85f);

	_window = SDL_CreateWindow("SkiOpen", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, _winWidth, _winHeight, SDL_WINDOW_SHOWN);
	if(!_window)
		panic("SDL_CreateWindow()", SDL_GetError());

	_renderer = SDL_CreateRenderer(_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!_renderer)
		panic("SDL_CreateRenderer()", SDL_GetError());

	SDL_SetRenderDrawColor(_renderer, 0xF2, 0xF2, 0xF2, 0xFF);

	srand((unsigned)time(nullptr));

	Data::instance()->load();
	Input::initController();
	_camera.setGeometry(Rect { 0, 0, _winWidth, _winHeight });

	_quadtree = new Quadtree(0, Rect { 0, 0, _winWidth, _winHeight });

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
	GameObject* x = _gameObjects.allocate();

	if(!x)
		panic("createGameObject()", "Could not create a new GameObject!");

	*x = GameObject();
	return x;
}

void Game::setLevel(int index)
{
	if(_currentLevel)
		_currentLevel->onExit();

	_currentLevel = _levels[index];
	_currentLevel->onLoad();
}

void Game::setup()
{
	_levels[L_MAIN] = new MainLevel();
	setLevel(L_MAIN);
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
	_quadtree->clear();

	// TODO Centre the Quadtree on the player.

	for(int i = 0; i < _gameObjects.capacity(); i++)
	{
		if(_gameObjects[i])
		{
			_gameObjects[i]->update();

			// Delete the GameObject if neccissary.
			if(_gameObjects[i]->getDeleteFlag())
			{
				_gameObjects[i]->setBehaviour(nullptr);
				_gameObjects.remove(i);
				continue;
			}

			_quadtree->insert(_gameObjects[i]);

			// Add the GameObject to the render list if neccissary.
			if(_camera.onScreen(_gameObjects[i]->spritePosition()))
				_renderList.add(_gameObjects[i]);
		}
	}

	checkCollisions();

	_camera.update();

	if(_currentLevel)
		_currentLevel->update();
}

void Game::render()
{
	SDL_RenderClear(_renderer);

	for(int i = 0; i < _renderList.size(); i++)
		_renderList[i]->render();
	_renderList.clear();

	SDL_RenderPresent(_renderer);
}

void Game::checkCollisions()
{
	// TODO
}

int Game::randomInRange(int min, int max)
{
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

Rect Game::centre(Rect original, Vector2 point)
{
	return Rect { point.x - (original.w / 2),
		point.y - (original.h / 2), original.w, original.h };
}

Rect Game::centre(Rect original, Vector2F point)
{
	return Game::centre(original, Vector2 { (int)point.x, (int)point.y });
}

Game* Game::_instance = nullptr;
