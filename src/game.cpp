#include <cstdlib>
#include <ctime>
#include "behaviours/behaviour.h"
#include "data.h"
#include "game.h"
#include "input.h"

#if _WIN32
#include <SDL_syswm.h>
#include <windows.h>
#include "../res/resource.h"
#endif

Game::Game()
{
	if(!_instance)
		_instance = this;
}

Game::~Game()
{
	if(_currentLevel)
		_currentLevel->onExit();

	delete Input::instance();
	delete Data::instance();

	const List<Level*>::Node* node = _levels.head();
	while(node)
	{
		delete node->data();
		node = _levels.next(node);
	}

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
		SDL_WINDOWPOS_CENTERED, _winWidth, _winHeight, SDL_WINDOW_HIDDEN);
	if(!_window)
		panic("SDL_CreateWindow()", SDL_GetError());
	setWindowIcon();

	_renderer = SDL_CreateRenderer(_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!_renderer)
		panic("SDL_CreateRenderer()", SDL_GetError());
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);

	srand((unsigned)time(nullptr));

	Data::instance()->load();
	_gameObjects.init(128);
	_camera.setGeometry(Rect{0, 0, _winWidth, _winHeight});
	_quadtree = new Quadtree(0, Rect{0, 0, _winWidth, _winHeight});

	SDL_ShowWindow(_window);
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
	int index = -1;
	GameObject* gObject = _gameObjects.nextFree(&index);

	if(!gObject)
		panic("createGameObject()", "Could not create a new GameObject!");

	gObject->_index = index;
	return gObject;
}

void Game::removeGameObject(GameObject* gameObject)
{
	_gameObjects.remove(gameObject->_index);
}

void Game::addLevel(Level* level)
{
	_levels.add(level);
}

void Game::setLevel(int index)
{
	if(_currentLevel)
		_currentLevel->onExit();

	_currentLevel = _levels[index];
	_currentLevel->onLoad();
}

void Game::handleInput()
{
	Input::instance()->clearEvents();

	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT:
			_quit = true;
			break;
		case SDL_CONTROLLERDEVICEADDED:
			Input::instance()->initController();
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			Input::instance()->closeController();
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP:
		case SDL_CONTROLLERAXISMOTION:
			Input::instance()->offerEvent(e);
			break;
		}
	}

	if(_player && _player->behaviour())
		_player->behaviour()->handleInput();

	if(_currentLevel)
		_currentLevel->handleInput();
}

void Game::update()
{
	_quadtree->clear();

	// Centre the Quadtree on the player.
	if(_player)
	{
		Rect bounds = { 0, 0, _winWidth, _winHeight };
		bounds = Game::centre(bounds, _player->physics()->position());
		_quadtree->setBounds(bounds);
	}

	for(int i = 0; i < _gameObjects.size(); i++)
	{
		GameObject* gObject = _gameObjects[i];
		if(gObject)
		{
			// Update the GameObject if possible.
			if(!_paused)
				gObject->update();

			// Delete the GameObject if neccissary.
			if(gObject->_delete)
			{
				_gameObjects.remove(i);
				continue;
			}

			_quadtree->insert(gObject);

			// Add the GameObject to the render list if neccissary.
			if(_camera.onScreen(gObject->spritePosition()))
				_renderList.add(gObject);
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

	const List<GameObject*>::Node* node = _renderList.head();
	while(node)
	{
		node->data()->render();
		node = _renderList.next(node);
	}
	_renderList.clear();

	if(_currentLevel)
		_currentLevel->render();

	SDL_RenderPresent(_renderer);
}

void Game::checkCollisions()
{
	if(!_player)
		return;

	List<GameObject*> possibleCollisions;
	_quadtree->retrieve(&possibleCollisions, _player);

	Hitbox playerHitbox = _player->physics()->hitbox();

	for(int i = 0; i < possibleCollisions.size(); i++)
	{
		if(possibleCollisions[i] == _player)
			continue;

		Hitbox otherHitbox = possibleCollisions[i]->physics()->hitbox();

		// Check for Hitbox overlap.
		if(playerHitbox.x < (otherHitbox.x + otherHitbox.w)
			&& (playerHitbox.x + playerHitbox.w) > otherHitbox.x)
		{
			if(playerHitbox.y < (otherHitbox.y + otherHitbox.h)
				&& (playerHitbox.y + playerHitbox.h) > otherHitbox.y)
			{
				_player->behaviour()->collide();
			}
		}
	}
}

void Game::pause()
{
	_paused = !_paused;
	_currentLevel->pause(_paused);
}

void Game::restart()
{
	if(!_currentLevel)
		return;

	if(_paused)
		return;

	_currentLevel->onExit();
	_currentLevel->onLoad();
}

void Game::setDrawColour(Colour colour)
{
	SDL_SetRenderDrawColor(_renderer, colour.r, colour.g, colour.b, colour.a);
}

int Game::randomInRange(int min, int max)
{
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

Rect Game::centre(Rect original, Vector2 point)
{
	return Rect{point.x - (original.w / 2),
		point.y - (original.h / 2), original.w, original.h};
}

Rect Game::centre(Rect original, Vector2f point)
{
	return Game::centre(original, point.vector2());
}

void Game::setWindowIcon()
{
#if _WIN32
	HICON icon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ICON1));
	if(!icon)
		return;

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_window, &wmInfo);

	HWND window = wmInfo.info.win.window;
	SendMessage(window, WM_SETICON, ICON_BIG, (LPARAM)icon);
	DestroyIcon(icon);
#endif
}

Game* Game::_instance = nullptr;
