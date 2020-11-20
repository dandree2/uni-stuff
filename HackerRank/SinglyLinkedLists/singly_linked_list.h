#pragma once
class SinglyLinkedListNode {
public:
	SinglyLinkedListNode(int);
	~SinglyLinkedListNode();

	int m_data;
	SinglyLinkedListNode* next;
};

class LinkedList {
public:
	LinkedList();
	~LinkedList();

	void push(int);
	void pop();
	void reverse();
	void print();

	SinglyLinkedListNode* head;
	SinglyLinkedListNode* tail;
};


