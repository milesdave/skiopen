#ifndef STRUCTURES_QUEUE_H_
#define STRUCTURES_QUEUE_H_

#include "list.h"

template <typename T>
class Queue
{
public:
	Queue() { }

	~Queue() { }

	// Adds an object to the end of the Queue.
	inline void offer(T object) { _list.add(object); }

	// Removes and returns the first object in the queue.
	inline T poll()
	{
		T object = _list[0];
		_list.remove(0);
		return object;
	}

	// Returns the first object in the Queue.
	inline T peek() const { return _list[0]; }

	// Removes everything from the Queue.
	inline void clear() { _list.clear(); }

	// Returns the number of objects in the Queue.
	inline int size() const { return _list.size(); }

private:
	// The list which will be used as a Queue.
	List<T> _list;
};

#endif
