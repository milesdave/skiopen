#include "../gameobject.h"
#include "quadtree.h"

Quadtree::Quadtree() { }

Quadtree::Quadtree(int level, Rect bounds)
{
	_level = level;
	_bounds = bounds;
}

Quadtree::~Quadtree()
{
	for(int i = 0; i < 4; i++)
		if(_nodes[i])
			delete _nodes[i];
}

void Quadtree::clear()
{
	_gameObjects.clear();

	for(int i = 0; i < 4; i++)
	{
		if(_nodes[i])
		{
			_nodes[i]->clear();
			delete _nodes[i];
			_nodes[i] = nullptr;
		}
	}
}

void Quadtree::insert(GameObject* gameObject)
{
	if(_nodes[0])
	{
		int index = getIndex(gameObject->physics()->getHitbox());

		// Recursively insert into subnode.
		if(index != -1)
		{
			_nodes[index]->insert(gameObject);
			return;
		}
	}

	// GameObject now inserted into correct subnode.
	_gameObjects.add(gameObject);

	// Handle more GameObjects than this node should have.
	if(_gameObjects.size() > MAX_OBJECTS && _level < MAX_LEVELS)
	{
		// Node needs to be split.
		if(!_nodes[0])
			split();

		int i = 0;
		while(i < _gameObjects.size())
		{
			int index = getIndex(_gameObjects[i]->physics()->getHitbox());

			if(index != -1)
			{
				// Move GameObject to it's new node.
				_nodes[i]->insert(_gameObjects[i]);
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
	int index = getIndex(subject->physics()->getHitbox());

	// Recursively find the correct node.
	if(index != -1 && _nodes[0])
		_nodes[index]->retrieve(gameObjects, subject);
	else // Return all GameObjects from node.
		for(int i = 0; i < _gameObjects.size(); i++)
			gameObjects->add(_gameObjects[i]);

	return gameObjects;
}

void Quadtree::split()
{
	int subWidth = _bounds.w / 2;
	int subHeight = _bounds.h / 2;
	int x = _bounds.x;
	int y = _bounds.y;

	_nodes[0] = new Quadtree(_level + 1, Rect { x + subWidth, y, subWidth,
		subHeight });
	_nodes[1] = new Quadtree(_level + 1, Rect { x, y, subWidth, subHeight });
	_nodes[2] = new Quadtree(_level + 1, Rect { x, y + subHeight, subWidth,
		subHeight });
	_nodes[3] = new Quadtree(_level + 1, Rect { x + subWidth, y + subHeight,
		subWidth, subHeight });
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

	return 0;
}
