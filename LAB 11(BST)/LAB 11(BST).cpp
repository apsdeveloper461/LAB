#include<iostream>
#include<string>
#include<queue>
using namespace std;



class Patient {
	int ID;
	string name;
	double age;
	string admission_date;
public:
	Patient() :ID(NULL), name(NULL), age(NULL), admission_date(NULL) {}
	Patient(int id, string n, double a, string a_d) :ID(id), name(n), age(a), admission_date(a_d) {}
	void setId(int i) {
		this->ID = i;
	}
	void setName(string n) {
		this->name = n;
	}
	void setAge(double a) {
		this->age = a;
	}
	void setAdmissionDate(string a_d) {
		this->admission_date = a_d;
	}
	void print()const {
		cout << endl << "<<<       Patient Id : " << this->ID << "        >>>\n=> Patient Name : " << this->name << "\n=> Age : " << this->age << "\n=> Admission Date :" << this->admission_date << endl;
	}
	int getID() const {
		return this->ID;
	}
};
class Node {
	Patient* P;
	Node* Parent;
	Node* leftChild;
	Node* rightChild;
public:

	Node(Patient* P1) :P(P1), Parent(NULL), leftChild(NULL), rightChild(NULL) {}
	Node() :P(NULL), Parent(NULL), leftChild(NULL), rightChild(NULL) {}
	Node(Patient* P1,Node* n) :P(P1), Parent(n), leftChild(NULL), rightChild(NULL) {}
	void setPatient(Patient* p) {
		this->P = p;
	}
	void setParent(Node* n) {
		this->Parent = n;
	}
	void setLeftChild(Node* n) {
		this->leftChild = n;
	}
	void setRightChild(Node* n) {
		this->rightChild = n;
	}
	Node* getRight() {
		return this->rightChild;
	}
	Node* getLeft() {
		return this->leftChild;
	}
	Node* getParent() {
		return this->Parent;
	}
	int getIdOfPatient() {
		return P->getID();
	}
	Patient* getPatient() {
		return this->P;
	}
	
};


class BST {
	Node* insertRecursive(Node* node, Patient* patient,Node*Pnode) {
		if (node == nullptr) return new Node(patient,Pnode);

		if (patient->getID() < node->getIdOfPatient())
			node->setLeftChild(insertRecursive(node->getLeft(), patient,node));
		else if (patient->getID() > node->getIdOfPatient())
			node->setRightChild(insertRecursive(node->getRight(), patient,node));
		return node;
	}
	Node* searchRecursive(Node* node, int patientID) {
		if (node == nullptr || node->getIdOfPatient() == patientID) {
			cout << "here";
			if (node)
				cout << "ID"<< node->getIdOfPatient();
			return node;
		}

		if (patientID < node->getIdOfPatient())
			return searchRecursive(node->getLeft(), patientID);

		return searchRecursive(node->getRight(), patientID);
	}
	
	int findHght(Node* root) {
		if (root == NULL) {
			return -1; // Return -1 for height of an empty tree
		}
		int leftHeight = findHght(root->getLeft());
		int rightHeight = findHght(root->getRight());
		return max(leftHeight, rightHeight) + 1;
	}
	bool delete_Node_private(Node* node, int key) {
		cout << "Key " << key;
		Node* dnode = searchRecursive(node, key);
		if (!dnode) {  //check element is found or not 
			cout << "Not found";
			return false;
		}
		dnode->getPatient()->print();
		if (dnode->getLeft() && dnode->getRight()) {
			cout << "Hello";
		}
		//case 1:check the delete node is root node  or leaf node
		if (!(dnode->getParent() || dnode->getLeft() || dnode->getRight())) {
			cout << "isroot || isleaf";
			this->root = NULL;
			delete dnode;
			return true;
		}
		if (!(dnode->getLeft() || dnode->getRight())) {
			cout << " isleaf";
			if (dnode->getParent()->getLeft() == dnode) dnode->getParent()->setLeftChild(NULL);
			else dnode->getParent()->setRightChild(NULL);
			delete dnode;
			return true;
		}
		// case 2: if  only one child is present of deleted node 
		if (dnode->getLeft() && !dnode->getRight()) {  // check for if only left child id exists
			if (!dnode->getParent()) { // this root node 
				cout << "isroot || set child left to root";
				this->root = dnode->getLeft();
			}
			else if (dnode->getParent() && dnode->getParent()->getLeft() == dnode) { // this is check is node which i want to delete is left child of your parent element or not
				cout << "check parent has left || set child left to root to root left";
				dnode->getParent()->setLeftChild(dnode->getLeft());
			}
			else if (dnode->getParent() && dnode->getParent()->getRight() == dnode) { // this is check is node which i want to delete is right child of your parent element or not
				cout << "check parent has right || set child left to root to right";
				dnode->getParent()->setRightChild(dnode->getLeft());
			}
			delete dnode;
			return true;
		}
		if (dnode->getRight() && !dnode->getLeft()) {  // check for if only left child id exists
			if (!dnode->getParent()) { // this root node 
				cout << "isroot || set child right to root";
				this->root = dnode->getRight();
			}
			else if (dnode->getParent() && dnode->getParent()->getLeft() == dnode) { // this is check is node which i want to delete is left child of your parent element or not
				cout << "check parent has left || set child right to root left";
				dnode->getParent()->setLeftChild(dnode->getRight());
			}
			else if (dnode->getParent() && dnode->getParent()->getRight() == dnode) { // this is check is node which i want to delete is right child of your parent element or not
				cout << "check parent has right || set child right to root to right";
				dnode->getParent()->setRightChild(dnode->getRight());
			}
			delete dnode;
			return true;
		}
		//case 3 : if the delelete node have two child then find min and  called again this function
		if (dnode->getLeft() && dnode->getRight()) {
			Node* mnode = findMinNode(dnode);
			Patient* p = dnode->getPatient();
			dnode->setPatient(mnode->getPatient());
			mnode->setPatient(p);
			cout << " This is mnode :" << mnode->getIdOfPatient() << dnode->getIdOfPatient();
			return delete_Node_private(mnode,key);
		}
	}
public:
	Node* root;
	BST() :root(NULL) {}
	void insert(Patient* patient) {
		root = insertRecursive(root, patient,NULL);
	}
	//L,N,R 
	void inOrder(Node* node) {
		if (node != NULL) {
			inOrder(node->getLeft());
			cout  << node->getIdOfPatient() << " ";
			inOrder(node->getRight());
		}
	}
	void decendingOrder(Node* node) {
		if (node != NULL) {
			decendingOrder(node->getRight());
			cout  << node->getIdOfPatient() << " ";
			decendingOrder(node->getLeft());
		}
	}
	//N,L,R
	void preOrder(Node* node) {
		if (node != nullptr) {
			cout  << node->getIdOfPatient() << " ";
			postOrder(node->getLeft());
			postOrder(node->getRight());
		}
	}
	//L,R,N 
	void postOrder(Node* node) {
		if (node != nullptr) {
			postOrder(node->getLeft());
			postOrder(node->getRight());
			cout  << node->getIdOfPatient() << " ";
		}
	}
	Node* searchNode(int id) {
		return searchRecursive(root, id);
	}
	
	Node* findMinNode(Node * n) {
		if (!n->getLeft()) return n;
		return findMinNode(n->getLeft());
	}
	
	int findHeight() {
		return findHght(this->root);
	}
	
	void levelOrder(Node* root) {
		if (root == NULL) {
			return;
		}

		queue<Node*> q;
		q.push(root);

		while (!q.empty()) {
			Node* current = q.front();
			q.pop();
			cout << current->getIdOfPatient() << " ";

			if (current->getLeft() != NULL) {
				q.push(current->getLeft());
			}
			if (current->getRight() != NULL) {
				q.push(current->getRight());
			}
		}
	}
	bool deleteNode(int key) {
		return delete_Node_private(this->root, key);
	}


};

int main() {
	Patient* P1 = new Patient(50, "Ferozi", 18.9, "12/02/2023");
	Patient* P2 = new Patient(30, "Alam", 12.9, "11/01/2023");
	Patient* P3 = new Patient(70, "rafey", 14.9, "17/02/2024");
	Patient* P4 = new Patient(20, "Mehboob", 18.9, "11/02/2023");
	Patient* P5 = new Patient(40, "Mehboob", 18.9, "11/02/2023");
	Patient* P6 = new Patient(10, "Noor", 1.9, "1/02/2023");
	Patient* P7 = new Patient(25, "Kainat", 0.9, "28/05/2006");
	Patient* P8 = new Patient(60, "Amber", 5.9, "17/01/2021");
	Patient* P9 = new Patient(80, "Itriza", 13.9, "12/02/2003");
	BST* bst = new BST();
	bst->insert(P1);
	bst->insert(P2);
	bst->insert(P3);
	bst->insert(P4);
	bst->insert(P5);
	bst->insert(P6);
	bst->insert(P7);
	bst->insert(P8);
	bst->insert(P9);


	cout << "Display in InOrder: \n";
	bst->inOrder(bst->root);

	//cout << "Height of Tree:\n" <<bst->findHeight();
	//cout << "Level Display";
	//bst->levelOrder(bst->root);

	bst->deleteNode(30);
	cout << "Display in InOrder: \n";
	bst->inOrder(bst->root);

	/*Node*n=bst->searchNode(30);
	if (n) {
		cout << "Yeas";
	}*/
	/*int x;
	cout << "Enter a Patient Id  to find : ";
	cin >> x;
	Node* res = bst->searchNode(x);
	if (res) {
		res->getPatient()->print();
	}
	else {
		cout << "Not Found";
	}*/


	return 0;
}