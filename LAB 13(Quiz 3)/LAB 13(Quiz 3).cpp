// LAB 13(Quiz 3).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;


class Node {
    int data;
    Node* Parent;
    Node* Left;
    Node* Right;

public:
	Node() :data(NULL), Parent(NULL), Left(NULL),Right(NULL) {}
	Node(Node* P, int d) :data(d), Parent(P) {}
	void setParent(Node* n) {
		this->Parent = n;
	}
	void setLeftChild(Node* n) {
		this->Left = n;
	}
	void setRightChild(Node* n) {
		this->Right = n;
	}
	Node* getRight() {
		return this->Right;
	}
	Node* getLeft() {
		return this->Left;
	}
	Node* getParent() {
		return this->Parent;
	}
	int getData() {
		return this->data;
	}
};


class BST {
	Node* root;
	Node* insertRecursive(Node* node, int data, Node* Pnode) {
		if (node == nullptr) return new Node(Pnode, data);

		if (data < node->getData())
			node->setLeftChild(insertRecursive(node->getLeft(), data, node));
		else if (data > node->getData())
			node->setRightChild(insertRecursive(node->getRight(), data, node));
		return node;
	}
	void inOrder(Node* r) {
		if (r != NULL) {
			inOrder(r->getLeft());
			cout << r->getData() << " ";
			inOrder(r->getRight());

		}
	}
	Node* searchWith_MAD(Node* r, int x, Node* mn,int min) {
			if (r == nullptr ) {
				return mn;
			}
			if (min==-1 && r->getData()<=x) {
				min = (x - r->getData());
				mn = r;
			}
			else {
				if ((r->getData()<=x) && (x - r->getData()) < min) {
					min = (x - r->getData());
					mn = r;
				}

			}

			if (x < r->getData())
				return searchWith_MAD(r->getLeft(),x,mn,min);

			return searchWith_MAD(r->getRight(),x,mn,min );
		
	}
	//task 02
	void getProduct(Node* r, int& sum) {
		if (r == NULL) {
			return;
		}

		sum = sum * r->getData();
		getProduct(r->getRight(), sum);
	}



	void MaximumProduct(Node* r, int& maxProduct) {
		if (r == NULL) {
			return;
		}

		int x = 1;
		getProduct(r, x);
		

		if (x > maxProduct) {
			maxProduct = x;
		}
		MaximumProduct(r->getLeft(), maxProduct);
		MaximumProduct(r->getRight(), maxProduct);
	}
public:
	BST() :root(NULL) {}

	void InsertValue(int x) {
		root = insertRecursive(root, x, NULL);
	}
	void InsertArray(int arr[], int size) {
		for (int i = 0; i < size; i++) {
			root = insertRecursive(root, arr[i], NULL);
		}
	}
	void Display() {
		inOrder(root);
	}
	int FindMinimumCloseValue(int x) {
		Node* res=searchWith_MAD(root, x, NULL, -1);
		if (res != NULL) {
			return res->getData();
		}
		else {
			cout << "Not found minimum value ";
			return -1;
		}
	}


	void GiveMaximumProduct() {
		int maxP=0;
		MaximumProduct(root,maxP);
		cout << "Maximum Product is : " << maxP;
	}
};

void task_01() {
	//task 01
	BST bst;
	bst.InsertValue(9);
	bst.InsertValue(4);
	bst.InsertValue(6);
	bst.InsertValue(3);
	bst.InsertValue(7);
	bst.InsertValue(5);
	bst.InsertValue(17);
	bst.InsertValue(22);
	bst.InsertValue(20);
	bst.Display();

	do
	{
		int x;
		cout << "Enter Input to find Minimum Absolute Difference from this value : ";
		cin >> x;
		cout << endl << "Output :: " << bst.FindMinimumCloseValue(x) << endl;
		cout << "Do you Want to search Again 1 for yes:";
		cin >> x;
		if (x != 1) break;
	} while (true);
	//bst.Display();
}
int main()
{
	//task 01 
	//task_01();



	//task 02
	const int SIZE = 7;
	BST bst1;
	int arr[] = { 13,11,9,5,6,1,20 };
	bst1.InsertArray(arr, SIZE);
	bst1.Display();
	bst1.GiveMaximumProduct();



	return 0;
}
