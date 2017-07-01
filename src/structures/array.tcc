#ifndef STRUCTURES_ARRAY_TCC_
#define STRUCTURES_ARRAY_TCC_

#include <cstdlib>
#include <new>

template <typename T>
Array<T>::Array() { }

template <typename T>
Array<T>::~Array()
{
	clear();
	free(_raw);
	delete[] _freeStack;
}

template <typename T>
void Array<T>::init(int size)
{
	_size = size;

	// Create the _array.
	_raw = (char*)calloc(sizeof(T), _size);
	_array = (T*)_raw;

	// Initialise the free stack.
	_freeStack = new int[_size];
	for(int i = 0; i < _size; i++)
		_freeStack[i] = i;
}

template <typename T>
T* Array<T>::nextFree()
{
	int index;
	if((index = freePop()) == -1)
		return nullptr;

	_used++;

	T* object = new(&_array[index]) T();
	return object;
}

template <typename T>
T* Array<T>::operator[](int index)
{
	if(freeContains(index))
		return nullptr;
	else
		return &_array[index];
}

template <typename T>
void Array<T>::remove(int index)
{
	_array[index].~T();
	_used--;
	freePush(index);
}

template <typename T>
void Array<T>::clear()
{
	for(int i = 0; i < _size; i++)
	{
		if(freeContains(i))
			continue;
		else
			_array[i].~T();
	}
}

template <typename T>
int Array<T>::freePop()
{
	if(_freeIndex == _size)
		return -1;

	int index = _freeStack[_freeIndex];
	_freeStack[_freeIndex] = -1;
	_freeIndex++;

	return index;
}

template <typename T>
void Array<T>::freePush(int index)
{
	_freeIndex--;
	_freeStack[_freeIndex] = index;
}

template <typename T>
bool Array<T>::freeContains(int index)
{
	for(int i = _freeIndex; i < _size; i++)
	{
		if(_freeStack[i] == index)
			return true;
	}

	return false;
}

#endif
