#ifndef STRUCTURES_LIST_TCC_
#define STRUCTURES_LIST_TCC_

template <typename T>
List<T>::Node::Node() { }

template <typename T>
List<T>::Node::~Node() { }

template <typename T>
List<T>::List() { }

template <typename T>
List<T>::~List()
{
	// TODO
}

template <typename T>
void List<T>::add(T data)
{
	// TODO
}

template <typename T>
T List<T>::operator[](int index)
{
	// TODO
	return nullptr;
}

template <typename T>
typename List<T>::Node* List<T>::next(Node* node)
{
	// TODO
	return nullptr;
}

template <typename T>
typename List<T>::Node* List<T>::previous(Node* node)
{
	// TODO
	return nullptr;
}

template <typename T>
void List<T>::remove(int index)
{
	// TODO
}

template <typename T>
void List<T>::clear()
{
	// TODO
}

#endif
