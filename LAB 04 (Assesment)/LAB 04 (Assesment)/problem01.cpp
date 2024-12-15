#include<iostream>

using namespace std;

class Node {
public:
	int data;
	Node* next;
	Node* prev;
	Node():data(NULL),next(NULL),prev(NULL){}
	Node(int v):data(v),next(NULL), prev(NULL) {}
};

class DoublyLInkedList {
public:
	Node* head;
	Node* tail;
	DoublyLInkedList() :head(NULL), tail(NULL){}
	void InsertAtStart(int v) {
		Node* n = new Node(v);
		if (head == NULL) {
			head = n;
			tail = n;

		}
		else {
			n->next = head;
			head->prev = n;
			head = n;
		}
	}
	void rotateByN(int n) {
		if (head == NULL || n < 1) {
			cout << "\nList is empty | Enter number is less than 1\n";
			return;
		}
		Node* current = head;
		int count = 1;

		while (current && current->next && count < n) {
			current = current->next;
			count++;
		}
		
		if (current == NULL && count < n) {
			cout << "\n Enter number is greater than size of linked list\n";
			return;
		}
		else if (current != NULL && count == n) {

			if (current == tail) {
				return;
			}
			Node* newhead = current->next;
			newhead->prev = NULL;
			current->next = NULL;
			Node* temp = newhead;

			while (temp && temp->next) {
				temp = temp->next;
			}
			temp->next = head;
			head->prev = temp;

			while (temp && temp->next) {
				temp = temp->next;
			}
			tail = temp;
			head = newhead;
			return;
		}

		
	}

	void Display() {
		Node* curr = head;
		while (curr) {
			cout << curr->data << "->";
			curr = curr->next;
		}
		cout << "NULL\n";
	}
};
//
//int main() {
//	DoublyLInkedList List;
//
//	List.InsertAtStart(5);
//	List.InsertAtStart(4);
//	List.InsertAtStart(3);
//	List.InsertAtStart(2);
//	List.InsertAtStart(1);
//	List.Display();
//	List.rotateByN(3);
//	List.Display();
//
//	List.rotateByN(4);
//	List.Display();
//
//	List.rotateByN(5);
//	List.Display();
//	List.rotateByN(6);
//	List.Display();
//
//
//	return 0;
//
//	
//}