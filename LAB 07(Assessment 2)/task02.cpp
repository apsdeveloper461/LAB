#include<iostream>
#include<string>
using namespace std;

class FNode {
	
	string funcName;
	string argument;
	
	FNode* callrFuntion;

	FNode* next;

public:
	FNode() :next(NULL),callrFuntion(NULL),funcName(NULL),argument(NULL){}
	FNode(string func_name,string arg,FNode* callr_function) :next(NULL), callrFuntion(callr_function), funcName(func_name), argument(arg) {}
	friend class FunctionSTACK;

};

class FunctionSTACK {
	FNode* top;
	
public:
	FunctionSTACK() :top(NULL) {}
	bool CallFunction(string funcName,string arguments) {
	
		FNode* n = new FNode(funcName, arguments, top);
		if (top) {
			cout << top->funcName << endl;
			n->next = top;
			top = n;
			return true;
		}
		top = n;
		return true;

	}

	void Return() {
		if (top) {
			FNode* cur = top;
			top = top->next;
		}
		else {
			cout << "\n-----( Already Empty Stack )-----\n";
		}

	}
	void DisplayFunctionCallHistory() {
		FNode* cur = top;

		cout << "\n------------------------------------------------------------";
		while (cur) {
			if (cur->callrFuntion)
				cout << endl << cur->funcName << "( " << cur->argument << " ) : " << cur->callrFuntion->funcName ;
			else
				cout << endl << cur->funcName << "( " << cur->argument << " ) : Parent Function" ;
			cur = cur->next;
		}
		cout << "\n------------------------------------------------------------\n";
	}
	void JumpTo(string funcName) {
		FNode* cur = top;
		while (cur) {
			if (cur->funcName == funcName) {
				break;
			}
			cur = cur->next;
		}
		if(cur)
			CallFunction(cur->funcName, cur->argument);
		else {
			cout << "\n---------( Not Found Function from list )------------\n";
		}
	}
	void JumpTo2(string func_name) {
		FNode* cur = top;
		while (cur) {
			if (cur->funcName == func_name) {
				break;
			}
			cur = cur->next;
		}
		if (cur) {
			
			while (top) {
				if (top->funcName == func_name) {
					break;
				}
				top = top->next;
			}

		}
	}
};


int main() {

	FunctionSTACK FS;
	FS.CallFunction("First", "2,4");
	FS.CallFunction("Second", "5");
	FS.DisplayFunctionCallHistory();
	FS.CallFunction("Third", "3,,4,5");
	FS.DisplayFunctionCallHistory();

	//FS.Return();
	//FS.DisplayFunctionCallHistory();
	//FS.JumpTo("Second");
	//FS.DisplayFunctionCallHistory();*/
	FS.JumpTo2("Second");
	FS.DisplayFunctionCallHistory();


	return 0;
}