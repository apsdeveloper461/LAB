#include<iostream>

using namespace std;

//functions
void print(int[], int);
void swapToVariable(int&, int&);
int bubbleSorting(int[], int);
int selectionSorting(int[], int);
void selectionSortWithPrinting(int[], int);
void bubbleSortWithPrinting(int[], int);

int main() {
    ////task 01 
    //const int SIZE = 10;
    //int arr1[SIZE] = { 45, 32, 19, 87, 12, 90, 67, 23, 55, 10 };
    //int arr2[SIZE] = { 45, 32, 19, 87, 12, 90, 67, 23, 55, 10 };
    //print(arr1,SIZE);
    //print(arr2,SIZE);
    //int noOfExchangeByBubbleSort = bubbleSorting(arr1, SIZE);
    //int noOfExchangeBySelectionSort= selectionSorting(arr2, SIZE);
    //cout << "Number of Exchange Using Bubble Sorting : " << noOfExchangeByBubbleSort << "\nNumber of Exchange Using Selection Sorting : " << noOfExchangeBySelectionSort << endl;
    //print(arr1, SIZE);
    //print(arr2, SIZE);



    ////task 02 
    ////here minutes after 12:00 
    ////90 means 
    //const int AT_SIZE = 10;
    //int arrivalTimes[AT_SIZE]= { 350, 120, 180, 240, 90, 60, 480, 300, 150, 210 };
    //cout << "Arrival Times before sorting : \n";
    //print(arrivalTimes, AT_SIZE);
    //cout << "\nHere Sorting Function Start : \n";
    //selectionSortWithPrinting(arrivalTimes, AT_SIZE);
    //cout << "\nArrival Times after sorting : \n";
    //print(arrivalTimes, AT_SIZE);


    ////task 03 
    //const int BK_SIZE=12;
    //int booksIds[BK_SIZE] = { 108, 101, 110, 103, 100, 107, 105, 111, 102, 109, 104, 106 };
    //cout << "Books Ids before sorting : \n";
    //print(booksIds, BK_SIZE);
    //cout << "\nHere Sorting Function Start : \n";
    //bubbleSortWithPrinting(booksIds, BK_SIZE);
    //cout << "\nBooks Ids after sorting : \n";
    //print(booksIds, BK_SIZE);


    return 0;
}

void print(int arr[], int s)
{
    for (int i = 0; i <= (s-1); i++) {
        cout << arr[i] << "  ";
    }
    cout << endl;
}

void swapToVariable(int& i, int& j) {
    int k = j;
    j = i;
    i = k;
}
int bubbleSorting(int arr[], int size) {
    bool isSwap;
    int numberOfExchange = 0;
    for (int i = 0; i < size - 1; i++) {
        isSwap = false;
        for (int j = 0; j < (size - 1) - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swapToVariable(arr[j], arr[j + 1]);
                isSwap = true;
                numberOfExchange++;
            }
        }
        if (!isSwap) {  // it means not exchange in full iteration , it means sort the array
            break;
        }

    }
    return numberOfExchange;
}

int selectionSorting(int arr[], int size) {
    int numberOfExchange = 0;

    for (int i = 0; i < (size - 1); i++) {
        int minIdx = i;
        for (int j = (i+1); j <= (size - 1); j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (i != minIdx) {
            swapToVariable(arr[i], arr[minIdx]);
            numberOfExchange++;
        }
    }
    return numberOfExchange;
}

void selectionSortWithPrinting(int arr[], int size)
{
    int numberOfExchange = 0;

    for (int i = 0; i < (size - 1); i++) {
        int minIdx = i;
        for (int j = (i + 1); j <= (size - 1); j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (i != minIdx) {
            swapToVariable(arr[i], arr[minIdx]);
            cout << "\nAfter Step " << i + 1 << " : ";
            print(arr, size);
        }
    }

}

void bubbleSortWithPrinting(int arr[], int size)
{
    bool isSwap;
    int numberOfExchange = 0;
    for (int i = 0; i < size - 1; i++) {
        isSwap = false;
        for (int j = 0; j < (size - 1) - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swapToVariable(arr[j], arr[j + 1]);
                isSwap = true;
                numberOfExchange++;
                cout << "After Step " << numberOfExchange << " : ";
                print(arr, size);
            }
        }
        if (!isSwap) {  // it means not exchange in full iteration , it means sort the array
            break;
        }

    }
}
