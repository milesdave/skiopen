#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include "camera.h"
#include "gameobject.h"
#include "levels/level.h"
#include "structures/array.h"
#include "structures/list.h"
#include "structures/quadtree.h"
#include "types.h"

class Game
{
public:
	Game();

	~Game();

	// Initialises important game systems.
	void init();

	// The main game loop.
	void loop();

	// Displays and error message and aborts.
	void panic(const char* title, const char* message) const;

	// Fills in the arguments with the window width and height.
	void windowDimentions(int* width, int* height) const;

	// Returns a pointer to a new GameObject to use.
	GameObject* createGameObject();

	// Removes a GameObject from use.
	void removeGameObject(GameObject* gameObject);

	// Adds a level to the game.
	void addLevel(Level* level);

	// Sets the current level.
	void setLevel(int index);

	// Sets the renderer draw colour.
	void setDrawColour(Colour colour);

	// Pauses or unpauses the game.
	void pause();

	// Restarts the current level.
	void restart();

	// Returns a pointer to the SDL renderer.
	inline SDL_Renderer* renderer() const { return _renderer; }

	// Returns the time taken to complete the last frame.
	inline float deltaTime() const { return _deltaTime; }

	// Returns a pointer to the camera object.
	inline Camera* camera() { return &_camera; }

	// Returns whether or not the game is paused.
	inline bool isPaused() const { return _paused; }

	// Sets the player GameObject.
	inline void setPlayer(GameObject* player) { _player = player; }

	// Clears the GameObject array.
	inline void clearGameObjects() { _gameObjects.clear(); }

	// Returns a pointer to this singular Game instance.
	static inline Game* instance() { return _instance; }

	// Returns a random integer in a range.
	static int randomInRange(int min, int max);

	// Returns a rectangle centred on a point.
	static Rect centre(Rect original, Vector2 point);
	static Rect centre(Rect original, Vector2f point);

private:
	// Handles user interaction.
	void handleInput();

	// Updates the game state.
	void update();

	// Renders the game.
	void render();

	// Checks if any GameObject has collided with another.
	void checkCollisions();

	// Sets the window icon to the .exe icon.
	void setWindowIcon();

	// Frame rate.
	static constexpr unsigned int FPS = 60;

	// Frame rate in milliseconds.
	static constexpr unsigned int TIME_STEP = (unsigned int)(1000 / FPS);

	// The time taken to complete the last frame.
	float _deltaTime = 1.0f / (float)FPS;

	// The window dimentions.
	int _winWidth, _winHeight;

	// Whether or not the game should exit.
	bool _quit = false;

	// Whether or not the game is paused.
	bool _paused = false;

	// The singular Game instance.
	static Game* _instance;

	// SDL window structure.
	SDL_Window* _window = nullptr;

	// SDL renderer structure.
	SDL_Renderer* _renderer = nullptr;

	// The camera object.
	Camera _camera;

	// Array of all GameObjects.
	Array<GameObject> _gameObjects;

	// List of GameObjects to render.
	List<GameObject*> _renderList;

	// List of levels.
	List<Level*> _levels;

	// Pointer to the current level.
	Level* _currentLevel = nullptr;

	// Quadtree for collision detection.
	Quadtree* _quadtree = nullptr;

	// The player GameObject.
	GameObject* _player = nullptr;
};

#endif
