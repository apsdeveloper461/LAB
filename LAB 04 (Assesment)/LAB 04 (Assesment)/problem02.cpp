#include<iostream>

using namespace std;

class SNode {
	int data;
	SNode* next;
public:
	SNode():data(NULL),next(NULL){}
	SNode(int v):data(v),next(NULL){}
	friend class SingleLinkedList;
};
class SingleLinkedList {
	SNode* head;
public:
	SingleLinkedList():head(NULL){}
	void InsertAtStart(int v) {
		SNode* n = new SNode(v);
		if (head == NULL) {
			head = n;
		}
		else {
			n->next = head;
			head = n;
		}
	}
	//delete n nodes from m node
	void skipMdeleteN(int m, int n) {
		if (head == NULL || n <= 0 || m < 1) {
			cout << "\nLinked list is empty | removing number of node is equal to or less than 1 | m is less than 1\n";
			return;
		}
		SNode* curr = head;
		while (curr) {
			int count = 1;
			while (curr && curr->next && count < m) {
				curr = curr->next;
				count++;
			}
			if (curr == NULL && curr->next == NULL) {
				cout << "\nn is greater tahn linkedlist nodes\n";
				return;
			}
			SNode* temp = curr->next;
			curr->next = NULL;

			SNode* temp1 = temp;
			int ncount = 1;
			cout << "n : " << n << endl;
			while (temp && ncount <= n) {
				cout << temp1->data << endl;
				temp = temp->next;
				delete temp1;
				temp1 = temp;
				ncount++;
			}
			if (temp) {
				curr->next = temp;
			}
			curr = curr->next;
		}
	}
	void Display() {
		SNode* curr = head;
		while (curr) {
			cout << curr->data << "->";
			curr = curr->next;
		}
		cout << "NULL\n";
	}
};

int main() {

	SingleLinkedList sList;
	sList.InsertAtStart(1);
	sList.InsertAtStart(10);
	sList.InsertAtStart(4);
	sList.InsertAtStart(9);
	sList.InsertAtStart(5);
	sList.InsertAtStart(3);
	sList.InsertAtStart(1);
	sList.InsertAtStart(9);
	sList.Display();

	sList.skipMdeleteN(1, 2);
	sList.Display();
	return 0;
}