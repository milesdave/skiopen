#ifndef STRUCTURES_LIST_H_
#define STRUCTURES_LIST_H_

template <typename T>
class List
{
public:
	List() { }

	~List();

	// adds an object at the index specified
	void add(T object, int index);

	// adds an object to the end of the list
	inline void add(T object) { add(object, m_size); }

	// returns a pointer to the object at the specified index
	T get(int index);

	// returns a pointer to the object at the specified index
	inline T operator[](int index) { return get(index); }

	// removes an object from the specified index
	void remove(int index);

	// removes all nodes from the list
	void clear();

	// returns the number of objects in the list
	inline int size() const { return m_size; }

private:
	// moves the access pointer to the specified index
	void move(int index);

	// node structure
	struct Node
	{
		T data;
		Node *next;
		Node *prev;
	};

	// pointer to the start of the list
	Node *m_head = nullptr;

	// pointer to the end of the list
	Node *m_tail = nullptr;

	// pointer to the current node to access
	Node *m_pointer = nullptr;

	// position of the current node to access
	int m_position = 0;

	// number of objects in the list
	int m_size = 0;
};

#include "list.tcc"

#endif
