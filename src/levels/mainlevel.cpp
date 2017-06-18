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
	_player->setBehaviour(new PlayerBehaviour());

	Game::instance()->camera()->setFocus(_player);
}

void MainLevel::update()
{
	// TODO
}

void MainLevel::render()
{
	// TODO
}

void MainLevel::pause()
{
	// TODO
}

void MainLevel::onExit()
{
	// TODO
}
