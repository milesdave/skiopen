#ifndef STRUCTURES_QUADTREE_H_
#define STRUCTURES_QUADTREE_H_

#include "../types.h"
#include "list.h"

typedef List<GameObject*> GOList;

class GameObject;

class Quadtree
{
public:
	Quadtree();

	// Initialises a Quadtree node with a level and area.
	Quadtree(int level, Rect bounds);

	~Quadtree();

	// Clears the tree recursively.
	void clear();

	// Inserts a GameObject into the tree.
	void insert(GameObject* gameObject);

	// Returns a list of GameObjects to check collisions for.
	GOList* retrieve(GOList* gameObjects, GameObject* subject);

	// Sets the area the node covers.
	inline void setBounds(Rect bounds) { _bounds = bounds; }

private:
	// Split node into four subnodes.
	void split();

	// Determines which subnode a GameObject can fit into.
	int getIndex(Hitbox hitbox);

	// Maximum number of GameObjects for a node.
	static constexpr int MAX_OBJECTS = 10;

	// Maximum number of levels for a node.
	static constexpr int MAX_LEVELS = 5;

	// Level of the node.
	int _level = 0;

	// Area of the node.
	Rect _bounds;

	// Subnodes of this node.
	Quadtree* _nodes[4];

	// GameObjects in this node.
	GOList _gameObjects;
};

#endif
