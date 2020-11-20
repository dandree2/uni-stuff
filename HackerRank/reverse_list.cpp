#include<iostream>

class Node {
public:
	Node(int);
	~Node();

	int m_data;
	Node* next;
};

class LinkedList {
public:
	LinkedList();
	~LinkedList();

	void push(int);
	void pop();
	void reverse();
	void print();
	
	Node* head;
	Node* tail;
};
Node::Node(int input) : m_data(1), next(nullptr) {
	this->m_data = input;
	std::cout << "Node constructed\n!";
}

Node::~Node() {
	std::cout << "Node destructed\n!";
}

LinkedList::LinkedList() : head(nullptr), tail(nullptr){

}

LinkedList::~LinkedList() {
	Node* curr = head;

	for (auto iterator = this->head; iterator != nullptr;)
	{
		curr = iterator;
		iterator = iterator->next;
		delete curr;
	}
}

void LinkedList::push(int new_element) {
	if (this->head == nullptr)
	{
		head = new Node(new_element);
		tail = head;
	}
	else
	{
		tail->next = new Node(new_element);
		tail = tail->next;
	}
}

void LinkedList::print() {
	for (auto iterator = this->head; iterator != nullptr; iterator = iterator->next)
	{
		std::cout << iterator->m_data << " " << "\n";
	}
}

void LinkedList::pop() {
	std::cout << "Popped: " << this->head->m_data << "\n";
	
	Node* to_destroy = this->head;
	head = head->next;
	delete to_destroy;
}

void LinkedList::reverse() {
	Node* prev = nullptr;
	Node* temp_next = nullptr;

	for (auto iterator = this->head; iterator != nullptr; ) {
		temp_next = iterator->next;
		iterator->next = prev;
		prev = iterator;
		iterator = temp_next;
	}
	head = prev;
}

int main()
{
	LinkedList instance;
	instance.push(2);
	instance.push(10);
	instance.push(50);
	instance.push(12);

	instance.reverse();
	instance.print();

	return 0;
}