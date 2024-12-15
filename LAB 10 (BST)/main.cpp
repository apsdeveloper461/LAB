#include<iostream>
#include<string>
using namespace std;



class Patient {
	int ID;
	string name;
	double age;
	string admission_date;
public:
	Patient():ID(NULL),name(NULL),age(NULL),admission_date(NULL){}
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
	int getID() const{
		return this->ID;
	}
};
class Node {
	Patient* P;
	Node* Parent;
	Node* leftChild;
	Node* rightChild;
public:
	Node() :P(NULL), Parent(NULL), leftChild(NULL), rightChild(NULL) {}
	Node(Patient* P1) :P(P1), Parent(NULL), leftChild(NULL), rightChild(NULL) {}
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
	Node* insertRecursive(Node* node, Patient* patient) {
		if (node == nullptr) return new Node(patient);

		if (patient->getID() < node->getIdOfPatient())
			node->setLeftChild(insertRecursive(node->getLeft(), patient));
		else if (patient->getID() > node->getIdOfPatient())
			node->setRightChild(insertRecursive(node->getRight(), patient));
		return node;
	}

public:
	Node* root;
	BST():root(NULL){}
	void insert(Patient* patient) {
		root = insertRecursive(root, patient);
	}

	void inOrder(Node* node) {
		if (node != NULL) {
			inOrder(node->getLeft());
			cout << "Patient ID: " << node->getIdOfPatient()<< endl;
			inOrder(node->getRight());
		}
	}
	void preOrder(Node* node) {
		if (node != nullptr) {
			cout << "Patient ID: " << node->getIdOfPatient() << endl;
			postOrder(node->getLeft());
			postOrder(node->getRight());
		}
	}
	void postOrder(Node* node) {
		if (node != nullptr) {
			postOrder(node->getLeft());
			postOrder(node->getRight());
			cout << "Patient ID: " << node->getIdOfPatient() << endl;
		}
	}
	Node* searchRecursive(Node* node, int patientID) {
		if (node == nullptr || node->getIdOfPatient() == patientID)
			return node;

		if (patientID < node->getIdOfPatient())
			return searchRecursive(node->getLeft(), patientID);

		return searchRecursive(node->getRight(), patientID);
	}




	

};

int main() {
	Patient* P1 = new Patient(5, "Ferozi", 18.9, "12/02/2023");
	Patient* P2 = new Patient(2, "Alam", 12.9, "11/01/2023");
	Patient* P3 = new Patient(3, "rafey", 14.9, "17/02/2024");
	Patient* P4 = new Patient(1, "Mehboob", 18.9, "11/02/2023");
	Patient* P5 = new Patient(10, "Mehboob", 18.9, "11/02/2023");


	BST* bst=new BST();
	bst->insert(P1);
	bst->insert(P2);
	bst->insert(P3);
	bst->insert(P4);
	bst->insert(P5);


	cout << "Display in InOrder: \n";
	bst->inOrder(bst->root);
	cout << "\nDisplay in PreOrder:\n";
	bst->preOrder(bst->root);
	cout << "\nDisplay in PostOrder:\n";
	bst->postOrder(bst->root);


	int x;
	cout << "Enter a Patient Id  to find : ";
	cin >> x;
	Node* res = bst->searchRecursive(bst->root, x);
	if (res) {
		res->getPatient()->print();
	}
	else {
		cout << "Not Found";
	}


	return 0;
}