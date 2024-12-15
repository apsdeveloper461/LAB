#include<iostream>
#include<iomanip>
#include<string>
using namespace std;


                                             ////using arrray 
//#define MAX 10
//class Stack {
//	int data[MAX];
//	int top;  // store the elemnt index in top which have 
//public:
//	Stack():top(-1){
//		for (int i = 0; i < MAX; i++)
//		{
//			data[i] = NULL;
//		}
//	}
//	bool push(int v) {
//		if (top >= (MAX - 1)) {
//			cout << "\n--(Stack is Full)--\n";
//			return false;
//		}
//		else {
//			data[++top] = v;
//			cout << endl << v << " is push into the Stack\n";
//			return true;
//		}
//	}
//	int pop(){
//		if (isEmpty()) {
//			cout << "\n--(Stack is Empty)--\n";
//			return -1;
//		}
//		else {
//			return data[top--];
//		}
//	
//	}
//
//	bool isEmpty() const{
//		return top < 0 ? true : false;
//	}
//	void display() {
//		if (!isEmpty()) {
//			cout << endl;
//			for (int i = 0; i < top; i++)
//			{
//				cout << "\t\t|| " << setw(5)<<data[i]  << "    ||\n";
//			}
//			cout << "\t\t==============\n";
//		}
//	}
//
//
//};
//int main() {
//	Stack s;
//
//	s.pop();
//	s.push(10);
//	s.push(0);
//	s.push(110);
//	s.push(11);
//	s.push(7);
//	s.push(90);
//
//	s.display();
//	s.pop();
//	s.display();
//	s.pop();
//	s.display();
//	s.pop();
//
//
//	return 0;
//}

//
                                               ////using linked list
//
//class Node {
//	char data;
//	Node* next;
//public:
//	Node() :data(NULL), next(NULL) {}
//	Node(char d) :data(d), next(NULL) {}
//	friend class LinkedListStack;
//};
//
//class LinkedListStack {
//	Node* head;
//public:
//	LinkedListStack():head(NULL){}
//	bool isEmpty() {
//		return head == NULL ? true : false;
//	}
//	bool push(char v) {
//		Node* n = new Node(v);
//		if (!isEmpty()) {
//			n->next = head;
//		}
//			head = n;
//			return true;
//	}
//	char pop() {
//		if (isEmpty()) {
//			cout << "\n\t--( Stack is Empty)--\n";
//			return 'x';
//		}
//		Node* temp = head;
//		head = head->next;
//		char x = temp->data;
//		delete temp;
//		return x;
//	}
//	char top() {
//		if (isEmpty()) {
//			cout << "\n\t--( Stack is Empty)--\n";
//			return 'x';
//		}
//		return head->data;
//	}
//
//	// checking sequencce of bracket 
//	//{}{(}){     wrong sequence 
//	//{{(})}}      wrong sequence 
//	//{{{()}}}{()}     right sequence
//	bool isBlanced(string str) {
//		for (char& ch : str) {
//			if (ch == '{' || ch == '(') {
//				push(ch);
//			}
//			else if (ch == '}' || ch == ')') {
//				if (isEmpty()) return false;
//				char topElement = top();
//				//cout << "Top Element: " << topElement;
//				if ((ch == '}' && topElement != '{') || (ch == ')' && topElement != '(')) return false;
//				pop();
//			}
//		}
//		return isEmpty();
//	}
//	void Dispaly() {
//		Node* cur = head;
//		if (!isEmpty()) {
//			cout << endl;
//			while(cur)
//			{
//				cout << "\t\t|| " << setw(5)<<	cur->data  << "    ||\n";
//				cur = cur->next;
//			}
//			cout << "\t\t==============\n";
//		}
//	}
//};
//
//
//int main() {
//
//
//	LinkedListStack ls;
//	string bracketSequence;
//	cout << "\nEnter the sequence of bracket: ";
//	cin >> bracketSequence;
//
//	if (ls.isBlanced(bracketSequence)) 	cout << endl << "---( Right Sequence )---\n";
//	else cout << endl << "---( wrong Sequence )---\n";
//	return 0;
//}





                                                            //Expression converstion from INfix to PostFix 

class SNode {
public:
	char data;
	SNode* next;
	SNode() :data(NULL) , next(NULL) {}
	SNode(char c) :data(c), next(NULL) {}
};

class SSTACK {
	SNode* head;
public:
	SSTACK() :head(NULL) {}
	bool isEmpty() {
		return head == NULL ? true : false;
	}
	bool push(char v) {
	    SNode* n = new SNode(v);
		if (!isEmpty()) {
			n->next = head;
		}
		head = n;
		return true;
	}
	char pop() {
		if (isEmpty()) {
			cout << "\n\t--( Stack is Empty)--\n";
			return NULL;
		}
		SNode* temp = head;
		head = head->next;
		char x = temp->data;
		delete temp;
		return x;
	}
	char top() {
		if (isEmpty()) {
			cout << "\n\t--( Stack is Empty)--\n";
			return NULL;
		}
		return head->data;
	}
	void Dispaly() {
		SNode* cur = head;
		if (!isEmpty()) {
			cout << endl;
			while (cur)
			{
				cout << "\t\t|| " << setw(5) << cur->data << "    ||\n";
				cur = cur->next;
			}
			cout << "\t\t==============\n";
		}
	}
	string InfixToPostfix(string str){
		string postfix = "";
		for (char &ch:str)
		{
			if (isalnum(ch))
				postfix += ch;
			else if (ch == '(')
				push(ch);
			else if (ch == ')' && !isEmpty()) {
				while (top() != '(' && top()) 
					postfix += pop();
				
					pop();
			}
			else if (checkOperatorPrecedence(ch)) {
				while (!isEmpty() && checkOperatorPrecedence(ch) <= checkOperatorPrecedence(top())) 
					postfix += pop();
				push(ch);			
			}
			else {
				cout << "\n---(Invalid Expression)---\n";
				return "";
			}
		}

		while (!isEmpty())
			postfix += pop();
		return postfix;
	}
	string InfixToPrefix(string str) {
		string n = "";
		for (int i = str.length(); i > 0;i-- ) {
			if (str[i - 1] == ')')
				n += '(';
			else if (str[i - 1] == '(')
				n += ')';
			else
				n += str[i - 1];
		}
		cout << "\nReverse String :: " << n << endl;;

		str=InfixToPostfix(n);
		n = "";
		for (int i = str.length(); i > 0; i--) {
			
				n += str[i - 1];
		}
		return n;
	}
	int checkOperatorPrecedence(char ch) {
		if (ch == '-' || ch == '+')
			return 1;
		else if (ch == '/' || ch == '*' || ch == '%')
			return 2;
		else if (ch == '^')
			return 3;
		else
			return 0;
	}
	
};



int main() {
	SSTACK ST;
	string str = "A+B*C+D";
	cout << ST.InfixToPrefix(str)<<endl;
	// Expected Postfix: AB*CD/+
	string str1 = "(A+B)*(C+D)";
	cout << ST.InfixToPrefix(str1) << endl;
	// Expected Postfix: A
	string str2 = "A*(B+C)/D-E";
	cout << ST.InfixToPrefix(str2) << endl;
	// Expected Postfix: ABC+*D/E-
	string str3 = "A+(B*C)/D";
	cout << ST.InfixToPrefix(str3) << endl;
	// Expected Postfix: ABC*D/+


	cout << ST.InfixToPostfix(str);




	return 0;
}