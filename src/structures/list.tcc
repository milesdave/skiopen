#ifndef STRUCTURES_LIST_TCC_
#define STRUCTURES_LIST_TCC_

template <typename T>
List<T>::~List()
{
	Node *current = m_head;
	while(current)
	{
		Node *next = current->next;
		delete current;
		current = next;
	}
}

template <typename T>
void List<T>::add(T object, int index)
{
	// index out of bounds
	if(index < 0 || index > m_size)
		return;

	Node *newNode = new Node();
	newNode->data = object;

	// head
	if(index == 0)
	{
		// empty
		if(!m_head)
		{
			newNode->data = object;
			newNode->next = newNode->prev = nullptr;
			m_tail = m_head = newNode;
		}
		else
		{
			// set new head to point to old head
			newNode->next = m_head;
			newNode->prev = nullptr;

			// set old head to point to new head
			m_head->prev = newNode;

			// update head
			m_head = newNode;
		}
	}
	// tail
	else if(index == m_size)
	{
		// set new tail to point to old tail
		newNode->next = nullptr;
		newNode->prev = m_tail;

		// set old tail to point to new tail
		m_tail->next = newNode;

		// update tail
		m_tail = newNode;
	}
	else
	{
		Node *oldNode = m_head;

		for(int i = 0; i < index; i++)
			oldNode = oldNode->next;

		// set new node next to old node next
		newNode->next = oldNode->next;

		// set new node next's previous to new node
		newNode->next->prev = newNode;

		// set old node next to new node
		oldNode->next = newNode;

		// set new node prev to old node
		newNode->prev = oldNode;
	}

	m_size++;
}

template <typename T>
T List<T>::get(int index)
{
	if(index < 0 || index >= m_size)
		return nullptr;

	move(index);

	return m_pointer->data;
}

template <typename T>
void List<T>::remove(int index)
{
	if(index < 0 || index >= m_size || m_size == 0)
		return;

	// head
	if(index == 0)
	{
		Node *newHead = m_head->next;

		delete m_head;

		// no nodes after removal
		if(!newHead)
		{
			m_head = m_tail = nullptr;
		}
		else
		{
			m_head = newHead;
			m_head->prev = nullptr;
		}

		// update pointer
		if(m_position == index)
		{
			m_position--;
			m_pointer = m_head;
		}
	}
	// tail
	else if(index == m_size - 1)
	{
		Node *newTail = m_tail->prev;

		delete m_tail;

		// update tail
		m_tail = newTail;
		m_tail->next = nullptr;

		// update pointer
		if(m_position == index)
		{
			m_position--;
			m_pointer = m_tail;
		}
	}
	else
	{
		Node *toDelete = m_head;

		for(int i = 0; i < index; i++)
			toDelete = toDelete->next;

		// set previous to point to next
		toDelete->prev->next = toDelete->next;

		// set next to point to previous
		toDelete->next->prev = toDelete->prev;

		// update pointer
		if(m_position == index)
		{
			m_position--;
			m_pointer = toDelete->prev;
		}

		delete toDelete;
	}

	m_size--;
}

template <typename T>
void List<T>::clear()
{
	Node *current = m_head;
	while(current)
	{
		Node *next = current->next;
		delete current;
		current = next;
	}

	m_head = m_tail = m_pointer = nullptr;
	m_size = m_position = 0;
}

template <typename T>
void List<T>::move(int index)
{
	// head
	if(index == 0)
	{
		m_position = 0;
		m_pointer = m_head;
	}
	// tail
	else if(index == m_size - 1)
	{
		m_position = m_size - 1;
		m_pointer = m_tail;
	}
	else
	{
		int difference = index - m_position;

		// forwards
		if(index > m_position)
		{
			for(int i = 0; i < difference; i++)
				m_pointer = m_pointer->next;
		}
		// backwards
		else if(index < m_position)
		{
			for(int i = 0; i > difference; i--)
				m_pointer = m_pointer->prev;
		}

		m_position = index;
	}
}

#endif
