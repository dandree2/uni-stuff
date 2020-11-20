#include<iostream>
#include"singly_linked_list.h"

SinglyLinkedListNode::SinglyLinkedListNode(int input) : m_data(1), next(nullptr) {
	this->m_data = input;
	std::cout << "Node constructed\n!";
}

SinglyLinkedListNode::~SinglyLinkedListNode() {
	std::cout << "Node destructed\n!";
}

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {

}

LinkedList::~LinkedList() {
	SinglyLinkedListNode* curr = head;

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
		head = new SinglyLinkedListNode(new_element);
		tail = head;
	}
	else
	{
		tail->next = new SinglyLinkedListNode(new_element);
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

	SinglyLinkedListNode* to_destroy = this->head;
	head = head->next;
	delete to_destroy;
}

void LinkedList::reverse() {
	SinglyLinkedListNode* prev = nullptr;
	SinglyLinkedListNode* temp_next = nullptr;

	for (auto iterator = this->head; iterator != nullptr; ) {
		temp_next = iterator->next;
		iterator->next = prev;
		prev = iterator;
		iterator = temp_next;
	}
	head = prev;
}