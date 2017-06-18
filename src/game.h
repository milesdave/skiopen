#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include "camera.h"
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

	// Returns a rectangle centred on a point.
	static Rect centre(Rect original, Vector2 point);

	// Returns a pointer to the SDL renderer.
	inline SDL_Renderer* renderer() const { return _renderer; }

	// Returns the time taken to complete the last frame.
	inline float deltaTime() const { return _deltaTime; }

	// Returns a pointer to the camera object.
	inline Camera* camera() { return &_camera; }

	// Returns a pointer to this singular Game instance.
	static inline Game* instance() { return _instance; }

	// Returns a random integer in a range.
	static int randomInRange(int min, int max);

private:
	// Gameplay setup before loop().
	void setup();

	// Handles user interaction.
	void handleInput();

	// Updates the game state.
	void update();

	// Renders the game.
	void render();

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

	// The singular Game instance.
	static Game* _instance;

	// SDL window structure.
	SDL_Window* _window = nullptr;

	// SDL renderer structure.
	SDL_Renderer* _renderer = nullptr;

	// The camera object.
	Camera _camera;
};

#endif
