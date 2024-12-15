#include<iostream>
#include<vector>
using namespace std;


class Node {
	int data;
	Node* next;

public:
	Node(int v):next(NULL),data(v){}
	Node():next(NULL){}
	//make friend class for accessing private member
	friend class SingleLinkedList;
};


class SingleLinkedList {
	Node* head;

public:
	SingleLinkedList() :head(NULL) {}
	Node* getHead() {
		return head;
	}
	void InsertAtBegin(int v) {
		//create a node object for storing in linked list
		Node* n = new Node(v);
		n->next = head;
		head = n;
	}
	void  InsertAtEnd(int v) {	
		//create a node object for storing in linked list
		Node* n = new Node(v);
		Node* temp = head;
		if (head == NULL) {
			head = n; return;
		}
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = n;
	}
	void InsertAfter(int idx, int v) {
			if (idx < 0) {
				cout << "\nOut of Bound Index\n";
				return;
			}
			if (idx == 0) {
				InsertAtBegin(v);
				return;
			}
			Node* temp = head;
			int count = 0;
			while (temp != NULL && count < idx - 1) {
				temp = temp->next;
				count++;
			}
			//cout << (temp == NULL && count == idx - 1) << " " << (temp == NULL) << (count == idx - 1) << " " << count;
			if (temp == NULL && count == idx) InsertAtEnd(v);
			else if (temp != NULL) {

				Node* n = new Node(v);
				n->next = temp->next;
				temp->next = n;
			}else cout << "\nOut of bound index \n";

		
	}

	void Update(int index, int value) {
		if (index < 0) {
			cout << "\n --Index Out of Bound--\n";
			return;
		}
		Node* temp = head;
		int count = 0;
		while (temp != NULL && count < index) {
			temp = temp->next;
			count++;
		}
		cout << "count " << count << "  index " << index << endl;
		if (count == index && temp!=NULL) {
			temp->data=value;
		}
		else {
			cout << "\n --Index Out of Bound--\n";
		}
	}
	int search(int v) {
		Node* temp = head;
		if (!head) return -1;
		int count = 0;
		while (temp != NULL) {
			if (temp->data == v) {
				return count;
			}
			temp = temp->next;
			count++;
		}

		return -1;
	}

	void Delete(int v) {
		int idx = search(v);
		if (idx == -1) {
			cout << "\nNot Found\n";
			return;
		}
		Node* temp = head;
		if (idx == 0) {
			head = temp->next;
			return;
		}
		for (int i = 0; i < idx-1; i++)
			temp = temp->next;
		Node* Next = temp->next;
		temp->next = Next->next;
	}
	void Sorting() {
		for (Node* list = head; list != NULL; list = list->next) {
			Node* min_node = list;

			for (Node* curr = list; curr != NULL; curr = curr->next) {
				if (curr->data < min_node->data) {
					min_node = curr;
				}
			}
			if (min_node != list) {
				int v = list->data;
				list->data = min_node->data;
				min_node->data = v;
			}

		}
	}
	void MergeList(SingleLinkedList& l) {
		Node* temp = head;
		while (temp->next) {
			temp = temp->next;
		}

		temp->next = l.getHead();
	}
	void reverse() {
		vector<int> v;
		Node* temp = head;
		while (temp != NULL) {
			v.push_back(temp->data);
			temp = temp->next;
		}
		temp = head;
		for (int i = 0; i < v.size(); i++)
		{
			if (temp != NULL) {
				temp->data = v[(v.size()-1) - i];
				temp = temp->next;
			}
		}
	}
	void Display() {
		Node* temp = head;
		cout << "\nSingle Linked List display now:\n";
		while (temp != NULL) {
			cout << temp->data;
			temp = temp->next;
			if (temp != NULL) cout << "->";

		}
	}


	void ReverseLinkedList() {
		Node* prev = NULL;
		Node* current = head;
		Node* Next = NULL;

		while (current) {
			Next = current->next;
			current->next = prev;
			prev = current;
			current = Next;
			
		}
		head = prev;

	}
	bool MakeCycle(int position) {
		Node* current = head;
		Node* newNode = NULL;
		int c = 0;

		while (current && current->next) {
			if (c == position) {
				newNode = current;
			}
			c++;
			current = current->next;
		}
		if (newNode) {
			current->next = newNode;
			return true;
		}
		return false;
	}
	bool DetectCycle() {
		Node* fast = head;
		Node* slow = head;

		while (fast && fast->next) {
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow) {
				return true;
			}
		}
		return false;
	}
	void RemoveCycle() {
		if (DetectCycle()) {
			Node* fast = head;
			Node* slow = head;

			while (fast && fast->next) {
				fast = fast->next->next;
				slow = slow->next;
				if (fast == slow) {
					 break;
				}
			}

			fast = head;

			while (fast->next != slow->next) {
				fast = fast->next;
				slow = slow->next;
			}
			slow->next = NULL;

		}
	}

	void FindMiddleNodeWithPointers() {
		Node* fast = head;
		Node* slow = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}

		if(slow)
			cout << "\nMiddle of Node is : " << slow->data  << " " << slow << endl;
	}
};



int main() {

	SingleLinkedList l;
	l.InsertAtBegin(12);
	l.FindMiddleNodeWithPointers();
	l.InsertAtEnd(13);
	l.FindMiddleNodeWithPointers();
	l.InsertAtEnd(15);
	l.FindMiddleNodeWithPointers();
	l.InsertAtEnd(1);
	l.FindMiddleNodeWithPointers();
	l.InsertAtEnd(-5);
	l.FindMiddleNodeWithPointers();
	l.InsertAtEnd(16);
	l.FindMiddleNodeWithPointers();
	l.Display();
	//l.ReverseLinkedList();
	/*int v;
	cout << "\nEnter th value which you want to search :";
	cin >> v;*/
	/*cout << "Enter index: ";
	cin >> idx;*/

	//l.InsertAfter(idx, v);
	//l.reverse();
	//l.Sorting();
	//l.Display();

	//l.Display();


	/*l.MakeCycle(2);

	cout << "Detecting a Cycle : " << l.DetectCycle();
	l.RemoveCycle();
	l.Display();*/

	return 0;
}