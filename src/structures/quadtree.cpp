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
	// TODO
}

GOList* Quadtree::retrieve(GOList* gameObjects, GameObject* subject)
{
	// TODO
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
