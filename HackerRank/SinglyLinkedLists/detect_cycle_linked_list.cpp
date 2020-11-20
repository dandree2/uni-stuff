#include<iostream>
#include<unordered_set>

#include"singly_linked_list.h"

bool has_cycle(SinglyLinkedListNode* head) {
	std::unordered_set<SinglyLinkedListNode*> temp;
	for (auto iterator = head; iterator != nullptr; iterator = iterator->next) {
		if (temp.empty() == true) {
			temp.insert(iterator);
		}
		else {
			for (auto var : temp) {
				if (var == iterator) {
					return true;
				}
			}

			temp.insert(iterator);
		}
	}

	return false;
}

int main() {

	LinkedList instance;
	instance.push(2);
	instance.push(50);
	instance.push(71);
	instance.push(66);
	instance.push(70);
	instance.push(80);
	instance.push(90);

	for (auto iterator = instance.head; iterator != nullptr; iterator = iterator->next) {
		std::cout << iterator->m_data << " ";
	}

	bool result = has_cycle(instance.head);

	std::cout << result;

	return 0;
}