#ifndef STRUCTURES_ARRAY_H_
#define STRUCTURES_ARRAY_H_

template <typename T>
class Array
{
public:
	// initialises with max number of elements
	Array(int capacity = 128);

	~Array();

	// returns a pointer to a free 'T'
	T* allocate();

	// access an element in the array
	T* operator[](int index);

	// remove an element from the array (mark for reuse)
	void remove(int index);

	// returns the number of (active) elements in the array
	inline int elements() const { return m_elements; }

	// returns the capacity of the array
	inline int capacity() const { return m_capacity; }

private:
	// pop a free index from the free stack
	int pop();

	// push a free index to the free stack
	void push(int free);

	// element structure stored in array
	struct Element
	{
		bool isActive = false;
		T object;
	};

	// number of (active) elements in the array
	int m_elements = 0;

	// max number of elements the array can hold
	int m_capacity = 0;

	// index for free stack
	int m_index = 0;

	// stack of free indicies
	int *m_freeStack = nullptr;

	// abstracted object array
	Element *m_objects = nullptr;
};

#include "array.tcc"

#endif
