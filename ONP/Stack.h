#ifndef _STACK_H_
#define _STACK_H_

template <class T>
class Stack
{
private:
	struct Node {
		T data;
		Node* next;
		Node* previous;
};
	int size;
	Node *head;
	Node *tail;
	
public:
	Stack();
	~Stack();
	Stack(Stack &&) = default;
	Stack & Stack::operator=(Stack &&) = default;
	void push(T element);
	bool empty();
	T peek();
	T pop();
	T popHead();
	int getSize();
	T & operator[](const int i);
};

template<class T>
Stack<T>::Stack()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}


template<class T>
inline void Stack<T>::push(T element)
{
	Node *temp = new Node;
	temp->data = element;
	temp->next = nullptr;

	if (tail != nullptr)
	{
		temp->previous = tail;
		tail->next = temp;
	}
	else
	{
		temp->previous = nullptr;
	}
	tail = temp;

	if (head == nullptr)
	{
		head = temp;
	}
	size++;
}

template<class T>
bool Stack<T>::empty()
{
	return size == 0;
}

template<class T>
T Stack<T>::peek()
{
	if (tail == nullptr)
		throw std::exception("Blad na stosie");
	return tail->data;
}

template<class T>
T Stack<T>::pop()
{	
	size--;
	Node* temp = tail;
	if (temp == nullptr)
		throw std::exception("Blad na stosie");
	T data = temp->data;
	tail = tail->previous;
	if (tail == nullptr)
		head = nullptr;
	delete temp;
	return data; 
}

template<class T>
inline T Stack<T>::popHead()
{
	size--;
	Node* temp = head;
	if (temp == nullptr)
		throw std::exception("Blad na stosie");
	T data = temp->data;
	head = head->next;
	if (head == nullptr)
		tail = nullptr;
	delete temp;
	return data;
}

template<class T>
int Stack<T>::getSize()
{
	return size;
}

template<class T>
inline T & Stack<T>::operator[](const int i)
{
	Node* current = head;

	for (int j = 0; j < size && j < i; j++)
	{
		current = current->next;
	}
	return current->data;
}

template<class T>
Stack<T>::~Stack()
{
	while (head != nullptr)
	{
		Node* next = head->next;
		delete head;
		head = next;
	}
}

#endif