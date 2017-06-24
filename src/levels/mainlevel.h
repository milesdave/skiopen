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
	// The player GameObject.
	GameObject* _player = nullptr;
};

#endif
