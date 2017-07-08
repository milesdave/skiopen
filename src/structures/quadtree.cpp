#include "../gameobject.h"
#include "quadtree.h"

Quadtree::Quadtree()
{
	for(int i = 0; i < 4; i++)
		_node[i] = nullptr;
}

Quadtree::Quadtree(int level, Rect bounds)
{
	_level = level;
	_bounds = bounds;

	for(int i = 0; i < 4; i++)
		_node[i] = nullptr;
}

Quadtree::~Quadtree()
{
	for(int i = 0; i < 4; i++)
	{
		if(_node[i])
			delete _node[i];
	}
}

void Quadtree::clear()
{
	_gameObjects.clear();

	for(int i = 0; i < 4; i++)
	{
		if(_node[i])
			_node[i]->clear();
	}
}

void Quadtree::insert(GameObject* gameObject)
{
	if(_node[0])
	{
		int index = getIndex(gameObject->physics()->hitbox());

		// Recursively insert into subnode.
		if(index != -1)
		{
			_node[index]->insert(gameObject);
			return;
		}
	}

	// GameObject now inserted into correct subnode.
	_gameObjects.add(gameObject);

	// Handle more GameObjects than this node should have.
	if(_gameObjects.size() > MAX_OBJECTS && _level < MAX_LEVELS)
	{
		// Node needs to be split.
		if(!_node[0])
			split();

		int i = 0;
		while(i < _gameObjects.size())
		{
			int index = getIndex(_gameObjects[i]->physics()->hitbox());

			if(index != -1)
			{
				// Move GameObject to it's new node.
				_node[index]->insert(_gameObjects[i]);
				_gameObjects.remove(i);
			}
			else
			{
				i++;
			}
		}
	}
}

GOList* Quadtree::retrieve(GOList* gameObjects, GameObject* subject)
{
	int index = getIndex(subject->physics()->hitbox());

	// Recursively find the correct node.
	if(index != -1 && _node[0])
		_node[index]->retrieve(gameObjects, subject);
	// Return all GameObjects from node.
	else
		*gameObjects = _gameObjects;

	return gameObjects;
}

void Quadtree::split()
{
	int w = _bounds.w / 2;
	int h = _bounds.h / 2;
	int x = _bounds.x;
	int y = _bounds.y;

	_node[0] = new Quadtree(_level + 1, Rect{x + w, y, w, h});
	_node[1] = new Quadtree(_level + 1, Rect{x, y, w, h});
	_node[2] = new Quadtree(_level + 1, Rect{x, y + h, w, h});
	_node[3] = new Quadtree(_level + 1, Rect{x + w, y + h, w, h});
}

int Quadtree::getIndex(Hitbox hitbox)
{
	int index = -1;
	float vertMid = (float)(_bounds.x + (_bounds.w / 2));
	float horizMid = (float)(_bounds.y + (_bounds.h / 2));

	// The Hitbox can fit into the top half.
	bool top = hitbox.y < horizMid && hitbox.y + hitbox.h < horizMid;

	// The Hitbox can fit into the bottom half.
	bool bottom = hitbox.y > horizMid;

	// The hitbox can fit into the left half.
	if(hitbox.x < vertMid && hitbox.x + hitbox.w < vertMid)
	{
		if(top)
			index = 1; // Top left quadrant.
		else if(bottom)
			index = 2; // Bottom left quadrant.
	}
	// The hitbox can fit into the right half.
	else if(hitbox.x > vertMid)
	{
		if(top)
			index = 0; // Top right quadrant.
		else if(bottom)
			index = 3; // Bottom right quadrant.
	}

	return index;
}
