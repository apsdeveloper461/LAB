#include<iostream>
#include<conio.h>
using namespace std;
//Statment
//at level 1 : 0/1 ,1/1
//at level 2 : 0/1,1/2,1/1
//at level 2 : 0/1,1/3,1/2,2/3,1/1
//at  level 4: 0/1,1/4,1/3,1/2,2/3,3/4,1/1
// a/b and c/d two fraction (a+b/b+d)
//denumerator is c+d<=n 
struct Node {
	int num;
	int denum;
	Node* next;

	Node(int num, int denum) :num(num), denum(denum), next(NULL) {}
};

class FareySequence {
	Node* head;

public:
	FareySequence() {
		//for level 1 
		head = new Node(0, 1);
		head->next = new Node(1, 1);
	}
	void GenerateFareySeqence(int n) {
		if (n < 1) {
			cout << "Always greater than 0"; return;
		}
		//generate 
		int current_level = 1;
		while (current_level < n) {
			current_level++;
			generateFractionInSequence(current_level);
		}
	}
	void generateFractionInSequence(int n) {
		Node* current = head;
		while (current->next) {

		int a = current->num;
		int b = current->denum;
		int c = current->next->num;
		int d = current->next->denum;

		Node* newNode = new Node(a + c, b + d);
		if (b + d <= n) {
			newNode->next = current->next;
			current->next = newNode;
		}
		current = current->next->next;

		}
	}
	void Display() {
		Node* temp = head;
		cout << endl;
		while (temp) {
			cout << temp->num << "/" << temp->denum;
			if (temp->next) cout << " , ";
			temp = temp->next;
		}
		cout << endl;
	}
};

int main() {
	do {
	int level;
	cout << "Enter the level for Grenerating Farey Sequence :";
	cin >> level;
	FareySequence FS;

	FS.GenerateFareySeqence(level);
	FS.Display();
	cout << "Enter e for exist otherwise ReCompile :";
	char ch;
	ch = _getche();
	if (ch == 'e' || ch == 'E') break;
	} while (true);

}