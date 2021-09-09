/**
*                    
*  Author:           Alex Ryan
*  Title:            Program 1
*  Course:           2143
*  Semester:         Fall 2021
* 
*  Description:
*        Linked List Example 
* 
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Node for our linked list
class Node {
    public:
    Node(int d, Node* n = nullptr, Node* p = nullptr) {  // cunstructor to make adding values easy
        data = d;
        next = n;
        prev = p;
    }
    int data;  // data value (could be a lot more values)
    Node* prev;
    Node* next;  // we always need a "link" in a linked list
};


class MyVector {
private:
    Node* head;  // base pointer of list
    Node* tail;
    int size;
public:
    /**
     * @brief Default Constructor 
     * 
     * Creates a new Linked List object.
     * 
     * @param void
     * @return void
     */
    MyVector() {
        head = nullptr;  // NULL = zeros
                      // and zeros imply empty
        tail = nullptr;
    }

    /**
     * @brief Overloaded Constructor 
     * 
     * Creates a new Linked List object from 
     * an array of values.
     * 
     * @param int* A - array of values
     * @param int size - size of array
     * 
     * @return void
     */
    MyVector(int *A, int arrSize) {
        head = nullptr;  // NULL = zeros
                      // and zeros imply empty
        tail = nullptr;
        for (int i = 0; i < arrSize; i++){
        head = new Node(A[i], head);

        if (head->next == nullptr){
            tail = head;
        }
        else{
            head->next->prev = head;
        }
        size++;
        }
        
    }

    MyVector(string filename) {
        ifstream fin; fin.open(filename);
        head = tail = nullptr;
        int temp;

        int i = 0;
        while(!fin.eof()) {
            fin >> temp;
            head = new Node(temp, head);
            if (head->next == nullptr){
                tail = head;
            }
            else {
                head->next->prev = head;
            }
            size++;
            i++;
        }
    }

    MyVector(const MyVector &V1) {
        head = tail = nullptr;
        for (int i = 0; i < V1.size; i++){
            head = new Node(V1.head->data, head);
            if (head->next == nullptr){
                tail = head;
            }
            else {
                head->next->prev = head;
            }
            size++;
        }
    }

    void print() {
        Node* temp = head;  // temp pointer copies head

        while (temp) {  // this loops until temp is NULL
                        // same as `while(temp != NULL)`

            cout << temp->data;  // print data from node
            if (temp->next) {
                cout << "->";
            }
            temp = temp->next;  // move to next node
        }
        cout << endl;
    }

    void pushFront(int val) {
        head = new Node(val, head);

        if (head->next == nullptr){
            tail = head;
        }
        else{
            head->next->prev = head;
        }
    }

    void pushFront(MyVector V2) {
        for (int i = 0; i < V2.size; i++){
            head = new Node(V2.head->data, head);
            if (head->next == nullptr){
                tail = head;
            }
            else {
                head->next->prev = head;
            }
            size++;
        }
    }

    void pushRear(int val) {
        tail = new Node(val, nullptr, tail);

        if (tail->prev == nullptr){
            head = tail;
        }
        else{
            tail->prev->next = tail;
        }
    }

    void pushRear(MyVector V2) {
        for (int i = 0; i < V2.size; i++){
            tail = new Node(V2.tail->data, nullptr, tail);
            if (tail->prev == nullptr){
                tail = head;
            }
            else {
                head->next->prev = head;
            }
            size++;
        }
    }

    void pushAt(int loc, int val) {

    }

    void inOrderPush(int val) {

    }

    int popFront() {
        if(!empty()){
            int popped = head->data;
            Node* killMe = head;
            head = head->next;
            delete killMe;
            return popped;
        }
        return -1;
    }

    int popRear() {
        if(!empty()){
            int popped = tail->data;
            Node* killMe = tail;
            tail = tail->prev;
            delete killMe;
            return popped;
        }
        return -1;
    }

    // int find(int val) {

    // }

    // int popAt(int loc) {

    // }

    bool empty(){
        return head == nullptr;
    }

    ~MyVector() {
        Node* travel = head;
        while(travel != nullptr){
            Node* tempnode = travel;
            travel = travel->next;
            delete tempnode;
        }
        head = nullptr;
    }
};

int main() {
int x = 0;

MyVector v1;
v1.pushFront(18);
v1.pushFront(20);
v1.pushFront(25);
v1.pushRear(18);
v1.pushRear(20);
v1.pushRear(25);
v1.print();

int A[] = {11,25,33,47,51};
MyVector v2(A,5);
v2.print();
cout << "we are here";

v2.pushFront(9);
v2.pushRear(63);
cout <<"we made it";

v1.pushRear(v2);
v1.print();

x = v1.popRear();
x = v1.popRear();
x = v1.popRear();
v1.print();
cout<<x<<endl;

MyVector v3(v1);
v3.print();

v3.pushFront(v2);
v3.print();
}