#ifndef STRUCTURES_LIST_H_
#define STRUCTURES_LIST_H_

template <typename T>
class List
{
public:
	List();

	~List();

	// Class which represents a List node.
	class Node
	{
	public:
		Node();

		~Node();

		// Returns a pointer to the node data.
		const T data() const { return &_data; }

	private:
		// The data stored in this node.
		T _data = nullptr;

		// Pointer to the next node.
		Node* _next = nullptr;

		// Pointer to the previous node.
		Node* _prev = nullptr;
	};

	// Adds a new node containing the specified data to the end of the List.
	void add(T data);

	// Returns a pointer to the node data at the specified index, nullptr if
	// index is not valid.
	T operator[](int index);

	// Returns a pointer to the node after the specified node.
	Node* next(Node* node);

	// Returns a pointer to the node before the specified node.
	Node* previous(Node* node);

	// Removes the node at the specified index.
	void remove(int index);

	// Removes all nodes from the List.
	void clear();

	// Returns the number of nodes in the List.
	inline int size() const { return _size; }

private:
	// Pointer to the first node.
	Node* _head = nullptr;

	// Pointer to the last node.
	Node* _tail = nullptr;

	// The number of nodes in the list.
	int _size = 0;
};

#include "list.tcc"

#endif
