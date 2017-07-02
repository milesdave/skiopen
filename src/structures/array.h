#ifndef STRUCTURES_ARRAY_H_
#define STRUCTURES_ARRAY_H_

template <typename T>
class Array
{
public:
	Array();

	~Array();

	// Creates the array with the specified size.
	void init(int size);

	// Returns a pointer to the next free object index, nullptr on fail.
	// Provide an int pointer in order to receive the index the object is from.
	T* nextFree(int* index = nullptr);

	// Returns a pointer to the object at the specified index, nullptr if there
	// is none.
	T* operator[](int index);

	// Removes (destructs) the object at the specified index and marks the index
	// as free.
	void remove(int index);

	// Removes (destructs) all objects in the array.
	void clear();

	// Returns the size of the array.
	inline int size() const { return _size; };

	// Returns the number of used indicies in the array.
	inline int used() const { return _used; }

	// Returns the number of free indicies in the array.
	inline int available() const { return _size - _used; }

private:
	// Pops a free index from the free index stack.
	int freePop();

	// Pushes a free index to the free index stack.
	void freePush(int index);

	// Returns true if the free stack contains the specified index.
	bool freeContains(int index);

	// The size of the array.
	int _size = 0;

	// The number of used indicies in the array.
	int _used = 0;

	// Index for the stack of free indicies.
	int _freeIndex = 0;

	// Stack of free indicies.
	int* _freeStack = nullptr;

	// The array of objects.
	T* _array = nullptr;

	// The raw memory block used for the object array.
	char* _raw = nullptr;
};

#include "array.tcc"

#endif
