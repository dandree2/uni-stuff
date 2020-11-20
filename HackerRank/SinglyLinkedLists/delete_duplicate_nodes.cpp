#include<iostream>

#include"singly_linked_list.h"

SinglyLinkedListNode* removeDuplicates(SinglyLinkedListNode* head) {
	auto list_iterator = head;
	
	int prev = head->m_data;
	LinkedList* temp = new LinkedList();

	for (; list_iterator != nullptr; list_iterator = list_iterator->next) {
		if (list_iterator == head) {
			temp->push(list_iterator->m_data);
			prev = list_iterator->m_data;
		}
		else {
			if (prev != list_iterator->m_data) {
				temp->push(list_iterator->m_data);
				prev = list_iterator->m_data;
			}
		}
	}

	return temp->head;
}


int main() {
	
	LinkedList instance;
	instance.push(2);
	instance.push(50);
	instance.push(50);
	instance.push(66);
	instance.push(70);
	instance.push(80);
	instance.push(80);
		
	SinglyLinkedListNode *new_list = removeDuplicates(instance.head);

	for (auto iterator = new_list; iterator != nullptr; iterator = iterator->next) {
		std::cout << iterator->m_data << " ";
	}

	return 0;
}