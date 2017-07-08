#ifndef STRUCTURES_LIST_TCC_
#define STRUCTURES_LIST_TCC_

template <typename T>
List<T>::Node::Node() { }

template <typename T>
List<T>::Node::Node(T data, Node* next, Node* prev)
{
	_data = data;
	_next = next;
	_prev = prev;
}

template <typename T>
List<T>::Node::~Node() { }

template <typename T>
List<T>::List() { }

template <typename T>
List<T>::~List()
{
	clear();
}

template <typename T>
void List<T>::operator=(const List<T>& other)
{
	if(_size > 0)
		clear();

	Node* current = other._head;
	while(current)
	{
		add(current->_data);
		current = current->_next;
	}
}

template <typename T>
void List<T>::add(T data)
{
	Node* node = nullptr;

	// The List is empty.
	if(_size == 0)
	{
		node = new Node(data, nullptr, nullptr);

		// Update the head and tail pointers.
		_head = _tail = node;
	}
	else
	{
		// Set the new node prev to point to the old tail.
		node = new Node(data, nullptr, _tail);

		// Set the old tail next to point to the new tail.
		_tail->_next = node;

		// Update the tail pointer.
		_tail = node;
	}

	_size++;
}

template <typename T>
T List<T>::operator[](int index) const
{
	Node* current = _head;

	for(int i = 0; i != index; i++)
		current = current->_next;

	return current->_data;
}

template <typename T>
void List<T>::remove(int index)
{
	if(index < 0 || index >= _size)
		return;

	// Remove the head.
	if(index == 0)
	{
		// Node which will become the new head.
		Node* next = _head->_next;

		delete _head;

		// Empty List after removal.
		if(!next)
		{
			_head = _tail = nullptr;
		}
		// Update the head pointer.
		else
		{
			_head = next;
			_head->_prev = nullptr;
		}
	}
	// Remove the tail.
	else if(index == _size - 1)
	{
		// Node which will become the new tail.
		Node* prev = _tail->_prev;

		delete _tail;

		// Update the tail pointer.
		_tail = prev;
		_tail->_next = nullptr;
	}
	// Remove somewhere in the middle.
	else
	{
		// The node to be deleted.
		Node* current = _head;

		// Move up the the node at the specified index.
		for(int i = 0; i < index; i++)
			current = current->_next;

		// Set the current previous next to the current next (bypass current).
		current->_prev->_next = current->_next;

		// Set the current next previous to the current previous (bypass current).
		current->_next->_prev = current->_prev;

		delete current;
	}

	_size--;
}

template <typename T>
void List<T>::clear()
{
	Node* current = _head;
	while(current)
	{
		Node* next = current->_next;
		delete current;
		current = next;
	}

	_head = _tail = nullptr;
	_size = 0;
}

#endif
