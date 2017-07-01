#ifndef LEVELS_MAIN_LEVEL_H_
#define LEVELS_MAIN_LEVEL_H_

#include "../text.h"
#include "../timer.h"
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
	void pause(bool paused) override;
	void onExit() override;

private:
	// Generates a 'tile' of obstacles centred on the player.
	void generateObstacles(int tileOffset = 250);

	// Updates the player's score.
	void updateScore();

	// Geometry of the obstacle 'tile'.
	Rect _obstacleTile;

	// Number of obstacles to spawn per tile.
	static constexpr int OBSTACLES = 40;

	// The width and height of the window.
	int _winWidth, _winHeight;

	// The player GameObject.
	GameObject* _player = nullptr;

	// Stats text objects in an array for convenience.
	Text _text[4];

	// The paused Text object.
	Text _pausedText;

	// The Timer object used for scoring.
	Timer _scoreTimer;

	// The current score for the player.
	int _score = 0;

	// The best score for the session.
	int _bestScore = 0;

	// The position of the player when scoring started (Y axis).
	float _startPosition = 0.0f;

	// The distance the player has travelled continuously (Y axis).
	float _distance = 0.0f;
};

#endif
