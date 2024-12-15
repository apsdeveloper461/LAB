//#include<iostream>
//#include<string>
//using namespace std;
//
//
//class Node {
//	int requestID;
//	int floor_number;
//	string request_time;
//	int priorty;
//	string status;
//	Node* next;
//	
//public:
//	Node() :next(NULL) {}
//	Node(int requestID, int floor_number, string request_time, int priority) :next(NULL),requestID(requestID), floor_number(floor_number), request_time(request_time), priorty(priority), status("pending") {}
//	friend class ElevatorQueue;
//
//};
//class ElevatorQueue {
//	Node* front;
//	//Node* current;
//	Node* rear;
//public:
//	ElevatorQueue() :front(NULL), rear(NULL) {}
//	void ShowRequests() {
//		Node* cur = front;
//		while(cur){
//			if (cur->status == "pending") {
//				cout << "\n -----(Data of this request Id : " << cur->requestID << " )-----" << endl;
//				cout << "FloorNumber : " << cur->floor_number << "\nPrority : " << cur->priorty << "\n request_time : " << cur->request_time << "\nStatus :" << cur->status << endl << endl;
//			}
//			cur = cur->next;
//		}
//	}
//	void ShowAllRequests() {
//		Node* cur = front;
//		while (cur) {
//				cout << "\n -----(Data of this request Id : " << cur->requestID << " )-----" << endl;
//				cout << "FloorNumber : " << cur->floor_number << "\nPrority : " << cur->priorty << "\n request_time : " << cur->request_time << "\nStatus :" << cur->status << endl << endl;
//			cur = cur->next;
//		}
//	}
//	bool RequestFloor(int requestID,int floor_number,string request_time,int priority) {
//		Node* n = new Node(requestID, floor_number, request_time, priority);
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
//
//	}
//	int ServeRequest() {
//		if (isEmpty())
//			return 404; 
//		else {
//			Node* temp = front;
//			Node* lowest = NULL;
//			bool isallServed = true;
//			while (temp) {
//				if (temp->status == "pending" ) {
//					lowest = temp;
//					isallServed = false;
//					break;
//				}
//				temp = temp->next;
//			}
//			if (isallServed) {
//				cout << "\n--( Queue is Empty for serving)---\n";
//				return 404;
//			}
//			temp = front;
//			while (temp) {
//				if (temp->status == "pending" && lowest->floor_number > temp->floor_number) {
//						lowest = temp;
//				}					
//				temp = temp->next;
//			}
//			lowest->status = "completed";
//			return lowest->floor_number;
//		}
//	}
//	bool isEmpty() {
//		return front == NULL ? true : false;
//	}
//	
//};
//int main() {
//
//	 ElevatorQueue Que;
//	 Que.RequestFloor(1, 3, "11:78 pm", 1);
//
//	 Que.RequestFloor(2, 3, "11:78 am", 3);
//
//	 Que.RequestFloor(3, 1, "11:78 pm", 1);
//
//	 Que.ShowRequests();
//	 Que.ServeRequest();
//	 Que.ShowRequests();
//	 Que.ServeRequest();
//	 Que.ShowAllRequests();
//
//
//
//
//	return 0;
//
//}