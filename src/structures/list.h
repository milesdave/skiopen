#ifndef STRUCTURES_LIST_H_
#define STRUCTURES_LIST_H_

template <typename T>
class List
{
public:
	List();

	~List();

	// Copies the contents of the other List.
	List(const List& other);

	// Copies the contents of the other List.
	void operator=(const List& other);

	// Class which represents a List node.
	class Node
	{
		friend class List;

	public:
		Node();

		// Creates a node with the given data and next and previous nodes.
		Node(T data, Node* next, Node* prev);

		~Node();

		// Returns the node data.
		T data() const { return _data; }

	private:
		// The data stored in this node.
		T _data;

		// Pointer to the next node.
		Node* _next = nullptr;

		// Pointer to the previous node.
		Node* _prev = nullptr;
	};

	// Adds a new node containing the specified data to the end of the List.
	void add(T data);

	// Returns a pointer to the node data at the specified index (not checked).
	// Only use this function to access a single node randomly. Use next() or
	// previous() for better sequential access from head() or tail().
	T operator[](int index) const;

	// Removes the node at the specified index.
	void remove(int index);

	// Removes all nodes from the List.
	void clear();

	// Returns a pointer to the node after the specified node. Use for
	// sequential access starting from head(). The list should not be modified
	// while using this for access.
	inline const Node* next(const Node* node) const { return node->_next; }

	// Returns a pointer to the node before the specified node. Use for
	// sequential access starting from tail(). The list should not be modified
	// while using this for access.
	inline const Node* previous(const Node* node) const { return node->_prev; }

	// Returns a pointer to the first node in the List.
	inline const Node* head() const { return _head; }

	// Returns a pointer to the last node in the List.
	inline const Node* tail() const { return _tail; }

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
