#include "../behaviours/goat.h"
#include "../behaviours/obstacle.h"
#include "../behaviours/player.h"
#include "../data.h"
#include "../game.h"
#include "../renderer.h"
#include "mainlevel.h"

MainLevel::MainLevel() { }

MainLevel::~MainLevel() { }

void MainLevel::onLoad()
{
	// Create the player object.
	_player = Game::instance()->createGameObject();
	_player->renderer()->setSprite(Data::instance()->sprite(SP_PLAYER_DOWN));
	_player->physics()->setFriction(Vector2F { 1.0f, 0.5f });
	_player->physics()->setMaxVelocity(Vector2F { 325.0f, 500.0f });
	_player->physics()->setMinVelocity(Vector2F { -325.0f, 0.0f });
	_player->physics()->setHitbox(Hitbox { 0, 0, 32, 32 });
	_player->setBehaviour(new PlayerBehaviour());

	Game::instance()->camera()->setFocus(_player);
	Game::instance()->setPlayer(_player);

	// Game title.
	GameObject* sign1 = Game::instance()->createGameObject();
	sign1->renderer()->setSprite(Data::instance()->sprite(SP_SIGN1));
	sign1->physics()->setPosition(Vector2F { -150.0f, -125.0f });
	sign1->setBehaviour(new ObstacleBehaviour());

	// Movement help sign.
	GameObject* sign2 = Game::instance()->createGameObject();
	sign2->renderer()->setSprite(Data::instance()->sprite(SP_SIGN2));
	sign2->physics()->setPosition(Vector2F { 75.0f, -100.0f });
	sign2->setBehaviour(new ObstacleBehaviour());

	// Other buttons sign.
	GameObject* sign3 = Game::instance()->createGameObject();
	sign3->renderer()->setSprite(Data::instance()->sprite(SP_SIGN3));
	sign3->physics()->setPosition(Vector2F { 170.0f, -140.0f });
	sign3->setBehaviour(new ObstacleBehaviour());

	// Goat sign.
	GameObject* sign4 = Game::instance()->createGameObject();
	sign4->renderer()->setSprite(Data::instance()->sprite(SP_SIGN4));
	sign4->physics()->setPosition(Vector2F { 175.0f, -60.0f });
	sign4->setBehaviour(new ObstacleBehaviour());

	Game::instance()->windowDimentions(&_winWidth, &_winHeight);

	// Setup the Text objects.
	for(int i = 0; i < 4; i++)
	{
		_text[i].setFont(Data::instance()->sheet(SH_FONT));
		_text[i].setPosition(Vector2 { 10, 12 * (i + 1) });
	}
	_pausedText.setFont(Data::instance()->sheet(SH_FONT));
	_pausedText.setPosition(Vector2 { (_winWidth / 2) - 30, (_winHeight / 2) - 10 });

	generateObstacles();
}

void MainLevel::update()
{
	if(_player->physics()->getPosition().y > _obstacleTile.y)
		generateObstacles(_winHeight);
}

void MainLevel::render()
{
	for(int i = 0; i < 4; i++)
		_text[i].render();
	_pausedText.render();
}

void MainLevel::pause(bool paused)
{
	_scoreTimer.pause();
	_pausedText.setText(paused ? "PAUSED!" : "");
}

void MainLevel::generateObstacles(int offset)
{
	// Player geometry.
	Rect player = _player->spritePosition();

	// Tile geometry.
	_obstacleTile.w = _winWidth * 3;
	_obstacleTile.h = _winHeight;
	_obstacleTile.x = player.x - ((_obstacleTile.w / 2) + (player.w / 2));
	_obstacleTile.y = player.y + offset;

	// Spawn obstacles
	for(int i = 0; i < OBSTACLES; i++)
	{
		// Random obstacle position.
		Vector2F randPosition = {
			(float)Game::randomInRange(_obstacleTile.x, _obstacleTile.x + _obstacleTile.w),
			(float)Game::randomInRange(_obstacleTile.y, _obstacleTile.y + _obstacleTile.h) };

		GameObject* obstacle = Game::instance()->createGameObject();
		obstacle->physics()->setPosition(randPosition);
		obstacle->physics()->setHitbox(Hitbox { 0, 0, 32, 32 });

		if(i == 0)
		{
			// Moving obstacle.
			GoatBehaviour* goat = new GoatBehaviour();
			GoatBehaviour::Direction direction =
				(GoatBehaviour::Direction)Game::randomInRange(0, 1);
			goat->setDirection(direction);
			obstacle->setBehaviour(goat);

			switch(direction)
			{
				case GoatBehaviour::Direction::Left:
					obstacle->renderer()->setSprite(Data::instance()->sprite(SP_GOAT_LEFT));
					break;
				case GoatBehaviour::Direction::Right:
					obstacle->renderer()->setSprite(Data::instance()->sprite(SP_GOAT_RIGHT));
					break;
			}
		}
		else
		{
			// Regular obstacle.
			obstacle->renderer()->setSprite(
				Data::instance()->sprite(Game::randomInRange(SP_OBSTACLE1, SP_OBSTACLE4)));
			obstacle->setBehaviour(new ObstacleBehaviour());
		}
	}
}
