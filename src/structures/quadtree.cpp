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
	// TODO
	return 0;
}
