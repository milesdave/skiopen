#ifndef LEVELS_MAIN_LEVEL_H_
#define LEVELS_MAIN_LEVEL_H_

#include "level.h"

class GameObject;

class MainLevel : public Level
{
public:
	MainLevel();

	~MainLevel() override;

	// Level functions.
	void onLoad() override;
	void update() override;
	void render() override;
	void pause() override;
	void onExit() override;

private:
	// Generates a 'tile' of obstacles centred on the player.
	void generateObstacles(int tileOffset = 250);

	// Geometry of the obstacle 'tile'.
	Rect _obstacleTile;

	// Number of obstacles to spawn per tile.
	static constexpr int OBSTACLES = 40;

	// The width and height of the window.
	int _winWidth, _winHeight;

	// The player GameObject.
	GameObject* _player = nullptr;
};

#endif
