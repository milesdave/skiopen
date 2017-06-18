#ifndef STRUCTURES_ARRAY_TCC_
#define STRUCTURES_ARRAY_TCC_

template <typename T>
Array<T>::Array(int capacity)
{
	m_capacity = capacity;
	m_objects = new Element[m_capacity];
	m_freeStack = new int[m_capacity];

	// setup free stack
	for(int i = 0; i < m_capacity; i++)
		m_freeStack[i] = i;
}

template <typename T>
Array<T>::~Array()
{
	delete[] m_objects;
	delete[] m_freeStack;
}

template <typename T>
T* Array<T>::allocate()
{
	int index;
	if((index = pop()) == -1)
		return nullptr;

	// set active flag at position
	m_objects[index].isActive = true;

	m_elements++;
	return &m_objects[index].object;
}

template <typename T>
T* Array<T>::operator[](int index)
{
	if(index < 0 || index >= m_capacity)
		return nullptr;

	return m_objects[index].isActive ? &m_objects[index].object : nullptr;
}

template <typename T>
void Array<T>::remove(int index)
{
	if(index < 0 || index >= m_capacity)
		return;

	push(index);

	m_objects[index].isActive = false;
	m_elements--;
}

template <typename T>
int Array<T>::pop()
{
	// array full
	if(m_index == m_capacity)
		return -1;

	int free = m_freeStack[m_index];

	// remove free spot
	m_freeStack[m_index] = -1;

	// increment index
	if(m_index < m_capacity)
		m_index++;

	return free;
}

template <typename T>
void Array<T>::push(int free)
{
	m_index--;
	m_freeStack[m_index] = free;
}

#endif
