//Queue Lab 

#include<iostream>
using namespace std;

////Queue with array 
//#define MAX_ARRAY_ELEMENT 10
//class ArrayQueue {
//	int front;   //store the index of top element means which element is remove first (first of the row where add a new person)
//	int rear;  // store the index where element is store (end of the row where person added)
//	int noOfElement;   // store the noOFElement wwhich store currently in the array 
//	int arrayData[MAX_ARRAY_ELEMENT];
//public:
//	ArrayQueue() :front(-1), rear(-1), noOfElement(0) {
//		for (int i = 0; i < MAX_ARRAY_ELEMENT; i++)
//			arrayData[i] = NULL;
//	}
//	bool push(int v) {
//		if (isFull()) 
//			return false;
//		rear = (rear + 1) % MAX_ARRAY_ELEMENT;
//		noOfElement++;
//		arrayData[rear] = v;
//		return true;
//	}
//	int pop() {
//		if (isEmpty())
//			return 404;
//		front = (front + 1) % MAX_ARRAY_ELEMENT;
//
//		int x= arrayData[front];
//		noOfElement--;
//		arrayData[front] = NULL;
//		return x;
//
//	}
//	int top() {
//		if (isEmpty())
//			return 404;
//		return arrayData[(front+1)%MAX_ARRAY_ELEMENT];
//	}
//	bool isEmpty() {
//		return noOfElement == 0 ? true : false;
//	}
//	bool isFull()
//	{
//		return noOfElement == MAX_ARRAY_ELEMENT ? true : false;
//	}
//	void display() {
//		for (int i = 0; i < MAX_ARRAY_ELEMENT; i++) {
//			cout << "\nINdex (" << i << ") :: " << arrayData[i];
//		}
//	}
//	
//};
//
//
//
//int main() {
//	ArrayQueue AQ;
//	cout << AQ.push(10) << endl;
//	cout << AQ.push(13) << endl;
//	cout << AQ.push(12) << endl;
//	cout << AQ.push(14) << endl;
//	cout << AQ.push(16) << endl;
//	cout << AQ.push(17) << endl; 
//	cout << AQ.push(112) << endl;
//	cout << AQ.push(132) << endl;
//	cout << AQ.push(104) << endl;
//	cout << AQ.push(108) << endl;
//	cout << AQ.push(1000) << endl;
//
//	AQ.display();
//
//	AQ.pop();
//	AQ.pop();
//	AQ.display();
//	cout << AQ.push(1222);
//	AQ.display();
//	cout << AQ.pop();
//	AQ.push(14444);
//	cout << AQ.pop() << endl;
//	cout << AQ.pop() << endl;
//	cout << AQ.pop() << endl;
//	cout << AQ.pop() << endl;
//	cout << AQ.pop() << endl;
//	cout << AQ.pop() << endl;
//	cout << AQ.pop()<<endl;
//	AQ.display();
//	cout << AQ.pop() << endl;
//	AQ.display();
//
//	cout << AQ.pop() << endl;
//	AQ.display();
//	cout << AQ.pop() << endl;
//	AQ.display();
//	return 0;
//}




////Queue Based on linked list 
//
//class Node {
//	int data;
//	Node* next;
//public:
//	Node() :data(NULL) , next(NULL) {}
//	Node(int v) :data(v), next(NULL) {}
//	friend class QueueWithLinkedList;
//
//};
//class QueueWithLinkedList {
//	Node* front;
//	Node* rear;
//public:
//	QueueWithLinkedList() :front(NULL), rear(NULL) {}
//	bool enqueue(int v) {
//		Node* n = new Node(v);
//		if (isEmpty()) {
//			rear = n;
//			front = n;
//			return true;
//		}
//		else {
//			rear->next = n;
//			rear = n;
//			return true;
//		}
//
//		return false;
//	}
//	int dequeue() {
//		if (isEmpty())
//			return 404;
//		else
//		{
//			Node* temp = front;
//			front = front->next;
//			if (!temp->next) {
//				rear = front;
//			}
//			int x = temp->data;
//			delete temp;
//			return x;
//		}
//	}
//
//	bool isEmpty() {
//		return front == NULL ? true : false;
//	}
//	void display() {
//		Node* temp = front;
//		cout << endl;
//		while (temp) {
//			cout << temp->data << " <- ";
//
//			temp = temp->next;
//		}
//	}
//};
//
//
//int main() {
//
//	QueueWithLinkedList QLL;
//
//
//	QLL.enqueue(10);
//	QLL.enqueue(20);
//	QLL.enqueue(40);
//	QLL.enqueue(80);
//
//	QLL.display();
//	QLL.dequeue();
//	QLL.dequeue();
//	QLL.enqueue(234);
//	QLL.display();
//	QLL.dequeue();
//	QLL.display();
//	QLL.dequeue();
//	QLL.display();
//
//
//	return 0;
//
//
//
//}




//Priorty Queue 
class PriorityNode {
	int data;
	int priorty;
	PriorityNode* next;
public:
	PriorityNode() :data(NULL),priorty(NULL), next(NULL) {}
	PriorityNode(int v,int p) :data(v),priorty(p), next(NULL) {}
	friend class PriorityQueue;

};
class PriorityQueue {
	PriorityNode* front;
	PriorityNode* rear;
public:
	PriorityQueue() :front(NULL), rear(NULL) {}
	bool enqueue(int value,int priorty) {
		PriorityNode* n = new PriorityNode(value,priorty);
		if (isEmpty()) {
			rear = n;
			front = n;
			return true;
		}
		else {
			rear->next = n;
			rear = n;
			return true;
		}

		return false;
	}
	int getHighestPriority() {
		if (isEmpty())
			return 404; // Or any value indicating an empty queue
		else {
			PriorityNode* temp = front;
			PriorityNode* highest = temp;

			// Store the highest priority node in 'highest'
			while (temp) {
				if (highest->priorty < temp->priorty) {
					highest = temp;
				}
				temp = temp->next;
			}

			// Remove the highest node from the linked list
			int x = highest->data;
			temp = front;

			// Special case if the highest node is the front
			if (highest == front) {
				if (highest == rear) {
					front = rear = NULL;  // List becomes empty
				}
				else {
					front = front->next;
				}
				delete highest; // No need to delete 'temp' here
				return x;
			}

			// Find the node before 'highest' to remove it
			while (temp->next != highest) {
				temp = temp->next;
			}

			temp->next = highest->next;

			// Special case if the highest node is the rear
			if (highest == rear)
				rear = temp;

			delete highest; // Correctly delete 'highest'
			return x;
		}
	}


	bool isEmpty() {
		return front == NULL ? true : false;
	}
	void display() {
		PriorityNode* temp = front;
		cout << endl;
		while (temp) {
			cout << temp->data << " <- ";

			temp = temp->next;
		}
	}
};


int main() {

	PriorityQueue PQ;

	PQ.enqueue(12, 0);
	PQ.enqueue(102, 1); PQ.enqueue(122, 5);
	PQ.enqueue(121, 0);
	PQ.display();

	PQ.getHighestPriority();
	PQ.display();
	PQ.getHighestPriority();
	PQ.display();
	PQ.getHighestPriority();
	PQ.display();
	PQ.getHighestPriority();
	PQ.display();
	return 0;



}