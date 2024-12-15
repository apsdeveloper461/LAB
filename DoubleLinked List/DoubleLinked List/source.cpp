#include<iostream>
#include<string>
using namespace std;
template <typename T>
class DNode {
public:
	T data;
	DNode<T>* next;
	DNode<T>* prev;

	DNode():data(NULL),next(NULL),prev(NULL){}
	DNode(T value):data(value),next(NULL),prev(NULL){}
};
template<typename T>
class DoublyLinkedList {
	DNode<T>* head;
	DNode<T>* tail;
public:
	DoublyLinkedList():head(NULL),tail(NULL){}
	bool isEmpty() {
		cout << head << " " << tail << endl;
		if (head == NULL) return true;
		else return false;
	}
	
	bool DeleteNodeByValue(T value) {
		DNode<T>* temp = head;
		while (temp) {
			if (temp->data == value) {
				if (temp == head && temp == tail) {
					head = NULL;
					tail = NULL;
				}
				else if (temp == head) {
					head = head->next;
					head->prev = NULL;
				}
				else if (temp == tail) {
					tail = tail->prev;
					tail->next = NULL;
				}
				else {
						temp->prev->next = temp->next;
						temp->next->prev = temp->prev;
				}
				delete temp;
				return true;
			}
			else {
				temp=temp->next;
			}
		}
		return false;
	}
	void Display() {
		DNode<T>* temp = head;
		cout << endl;
		while (temp != NULL) {
			cout << temp->data;
			temp = temp->next;
			if (temp != NULL) cout << "<->";
		}
	}

	void InsertAtPosition(int idx, T v) {
		DNode<T>* n = new DNode<T>(v);
		if (idx < 0) {
			cout << "Index is less than 0";
			return;
		}
		if (idx == 0 ) {
			if(head==NULL)
			head = tail = n;
			else {
				head->prev = n;
				n->next = head;
				head = n;
			}
			return;
		}

		DNode<T>* temp = head;
		int count = 0;
		while (temp && count < idx - 1) {
			temp = temp->next;
			count++;
		}

		if (temp) {
			if (count + 1 == idx) {
				n->next = temp->next;
				if (temp->next) {
					temp->next->prev = n;
				}
				else {
					tail = n;
				}
				temp->next = n;
			}
			cout << "Data at tail is " << tail->data;

		}
		else {
			cout << "Out of bound";
			return;
		}
	}
};

int main() {
	DoublyLinkedList<string> l;
	l.InsertAtPosition(1, "2w");

	l.Display();
	l.InsertAtPosition(0, "9a");

	l.Display();
	l.InsertAtPosition(1, "12f");

	l.Display();
	l.InsertAtPosition(1, "10d");

	l.Display();
	l.InsertAtPosition(3, "90c");

	l.Display();
	l.InsertAtPosition(5, "100a");
	l.Display();
	return 0;
}
