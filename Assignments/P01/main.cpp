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
/**
 * Node
 * 
 * Description:
 *      Template of Nodes used in the linked list
 * 
 * Public Methods:
 *      Node(int d, Node* n, Node* p) : Constructor
 *      int data : the data that is stored in the node
 *      Node* prev : points to the previous node if one exists
 *      Node* next : points to the next node if one exists
 * 
 * Private Methods:
 *      None
 * 
 * Usage: 
 *      Use the constructor to create a node 
 *      Use the first parameter to store integers
 *      Use the second and third to declare the address of the next
 *      and previous nodes respectively
 *      
 */
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

/**
 * MyVector
 * 
 * Description:
 *      A doubly linked list that acts as a custom vector class
 * 
 * Public Methods:
 *      - MyVector() 
 *      - MyVector(int *A, int arrSize)
 *      - MyVector(string filename)
 *      - MyVector(const MyVector &V1
 *      - void print()
 *      - void pushFront(int val)
 *      - void pushFront(MyVector V2)
 *      - void pushRear(int val)
 *      - void pushRear(const MyVector &V2)
 *      - void pushAt(int loc, int val)
 *      - int popFront()
 *      - int popRear()
 *      - int find(int val)
 *      - int popAt(int loc)
 *      - bool empty()
 *      - ~MyVector()
 * 
 * Private Methods:
 *      - Node* head
 *      - Node* tail
 * 
 * Usage: 
 *      - MyVector v1;
 *      - MyVector v2(A,5);
 *      - MyVector v4("input.dat");
 *      - MyVector(v1)
 *      - v1.print();
 *      - v1.pushFront(18);
 *      - v1.pushFront(v2)
 *      - v2.pushRear(63);
 *      - v3.pushRear(v2)
 *      - v2.pushAt(3, 4)
 *      - v2.pushFront(63);
 *      - v2.popRear()
 *      - v3.find(420)
 *      - v3.popAt(5)
 *      - bool empty()
 *      
 */

class MyVector {
private:
    Node* head;  // base pointer of list
    Node* tail;
public:
    int size;
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
        head = nullptr; // NULL = zeros
                        // and zeros imply empty
        tail = nullptr;
        for (int i = arrSize-1; i > -1; i--){ 
                                    //For loop that runs through the list
        head = new Node(A[i], head);

        if (head->next == nullptr){ //checks to see if there is more than 
            tail = head;            //one item in the list
        }
        else{
            head->next->prev = head;//Maintains the leftmost node as the head
        }
        size++;         // Checks the size of the list
        }
        
    }
    /* 
    * Public: MyVector(string filename)
    *
    * Description: 
    *       Default constructor that takes in a file and creates a list 
    * 
    * Parameters:
    *       string filename: The name of the file you would like to read in
    * 
    */
    MyVector(string filename) {
        ifstream fin; fin.open(filename);       //Open File
        head = tail = nullptr;
        int temp;

        int i = 0;
        while(!fin.eof()) {                     //Reads until end of file
            fin >> temp;
            head = new Node(temp, head);        //Creates new node
            if (head->next == nullptr){
                tail = head;
            }
            else {
                head->next->prev = head;
            }
            size++;
        }
    }
    /* 
    * Public: MyVector(const MyVector &V1)
    *
    * Description:
    *       Creates a copy of another vector
    * 
    * Parameters:
    *       Another MyVector
    * 
    * 
    */
    MyVector(const MyVector &V1) {
        head = tail = nullptr;              
        for (int i = 0; i < V1.size; i++){
            head = new Node(V1.head->data, head);   //Creates new node
            if (head->next == nullptr){
                tail = head;
            }
            else {
                head->next->prev = head;
            }
            size++;
        }
    }

    /*
    * Public : print()
    *
    * Description:
    *       prints any list that is called with the function.
    * 
    * Parameters:
    *       None  
    * 
    * Returns:
    *       None
    */
    void print() {
        Node* temp = head;  // temp pointer copies head

        while (temp) {  // this loops until temp is NULL
                        // same as `while(temp != NULL)`
            cout << temp->data;  // print data from node
            if (temp->next) {
                cout << ", ";
            }
            temp = temp->next;  // move to next node
        }
        cout << endl;
    }

    /*
    * Public : pushFront
    *
    * Description:
    *       Adds a value at the beginning of the list
    * 
    * Parameters:
    *       int val : What value you want to add to the list
    * 
    * Returns:
    *       None
    */

    void pushFront(int val) {
        head = new Node(val, head);     //Creates new node

        if (head->next == nullptr){
            tail = head;
        }
        else{
            head->next->prev = head;
        }
    }

    /*
    * Public : pushFront
    *
    * Description:
    *       Adds an entire other List at the beginning of this list
    * 
    * Parameters:
    *       MyVector : Another instance of MyVector
    * 
    * Returns:
    *       None
    */

    void pushFront(MyVector V2) {
        for (int i = 0; i < V2.size; i++){
            head = new Node(V2.head->data, head);   //Creates new node
            if (head->next == nullptr){
                tail = head;
            }
            else {
                head->next->prev = head;
            }
            size++;
        }
    }

    /*
    * Public : pushRear
    *
    * Description:
    *       Adds a value at the end of the list
    * 
    * Parameters:
    *       int val : What value you want to add to the end of list
    * 
    * Returns:
    *       None
    */

    void pushRear(int val) {
        tail = new Node(val, nullptr, tail);    //Creates new node

        if (tail->prev == nullptr){
            head = tail;
        }
        else{
            tail->prev->next = tail;
        }
    }

    /*
    * Public : pushRear
    *
    * Description:
    *       Adds an entire other List at the end of this list
    * 
    * Parameters:
    *       MyVector : Another instance of MyVector to the end of this list
    * 
    * Returns:
    *       None
    */

    void pushRear(const MyVector &V2) {
        Node* temp = V2.head;   //Creates new node
        while(temp) {
            pushRear(temp->data);
            temp = temp->next;
        }
    }

    /*
    * Public : pushAt
    *
    * Description:
    *       Replaces a value at a given location/index
    * 
    * Parameters:
    *       int loc : The location/index where you want to replace the int
    *       int val : The value you would like replace in the index
    * 
    * Returns:
    *       None
    */

    void pushAt(int loc, int val) {
        Node* travel = head;    //Creates new node
        int currentLoc = 0;   
        while(currentLoc != loc){
        if(currentLoc != loc) {
            travel = travel->next;
            currentLoc++;
        }
        else {
            travel->data = val;
            return;
        }
        }
    }

    /*
    * Public : popFront
    *
    * Description:
    *       Removes the foremost value in the list
    * 
    * Parameters:
    *       None
    * 
    * Returns:
    *       The popped int
    */

    int popFront() {
        if(!empty()){
            int popped = head->data;
            Node* killMe = head;    //Creates new temp node
            head = head->next;
            delete killMe;
            size--;
            return popped;
        }
        return -1;
    }

    /*
    * Public : popRear
    *
    * Description:
    *       Removes the last value in the list
    * 
    * Parameters:
    *       None
    * 
    * Returns:
    *       The popped int
    */

    int popRear() {
        if(!empty()){
            int popped = tail->data;
            Node* killMe = tail;        //Creates new temp node

            tail = tail->prev;
            killMe = nullptr;
            delete killMe;
            size--;
            return popped;
        }
        return -1;
    }

    /*
    * Public : find
    *
    * Description:
    *       Searched the entire list for a value and returns the location
    * 
    * Parameters:
    *       int val : The value you want to find the location of
    * 
    * Returns:
    *       The location of the int you are looking for
    */

    int find(int val) {
        Node* travel = head;    //Creates new node
        int index = 0;
        for (int i = 0; i < size; i++) {
            if (travel->data == val) {
                return index;
            }
            else if(travel->next == nullptr) {
                return -1;
            }
            else {
                index++;
            }
        }
        return 0;
    }

    /*
    * Public : popAt
    *
    * Description:
    *       Removes the value at the given location
    * 
    * Parameters:
    *       int loc : the location of the value you would like to remove
    * 
    * Returns:
    *       The popped int
    */
    int popAt(int loc) {
        Node* travel = head;        //Creates new node
        int currentLoc = 0;
        while(currentLoc != loc){
        if(currentLoc != loc) {
            travel = travel->next;
            currentLoc++;
        }
        else {
            int temp = travel->data;
            travel->prev->next = travel->next;
            delete travel;
            return temp;
        }
        }
        return 0;
    }

    /*
    * Public : empty
    *
    * Description:
    *       boolean function that checks to see if the list is empty
    * 
    * Parameters:
    *       None
    * 
    * Returns:
    *       T/F if the function is empty
    */
    bool empty(){
        return head == nullptr;
    }

    /*
    * Public : ~MyVector()
    *
    * Description:
    *       Destructor, moves through the list and deletes all nodes
    * 
    * Parameters:
    *       None
    * 
    * Returns:
    *       None
    */
    ~MyVector() {
        Node* travel = head;        //Creates new node
        while(travel != nullptr){
            Node* tempnode = travel;//Creates new temp node
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
// [25, 20, 18, 18, 20, 25]

int A[] = {11,25,33,47,51};
MyVector v2(A,5);
v2.pushRear(v1);
v2.print();
// [11, 25, 33, 47, 51]

v2.pushFront(9);
// v2.inOrderPush(27);
v2.pushRear(63);
v2.print();
// [9, 11, 25, 27, 33, 47, 51, 63]
v1.pushRear(v2);
v1.print();
// [25, 20, 18, 18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]

x = v1.popFront();
x = v1.popFront();
x = v1.popFront();
v1.print();
// [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
cout<<x<<endl;
// 18

x = v1.popRear();
x = v1.popRear();
x = v1.popRear();
v1.print();
// [18, 20, 25, 9, 11, 25, 27, 33]
cout<<x<<endl;
//47

x = v2.popAt(3);
v2.print();
// [9, 11, 25, 33, 47, 51, 63]
cout<<x<<endl;
// 27

x = v2.find(51);
cout<<x<<endl;
// 5

x = v2.find(99);
cout<<x<<endl;
// // -1

// MyVector v3(v1);
//v3.print();
// [18, 20, 25, 9, 11, 25, 27, 33]

//v3.pushFront(v2);
//v3.print();
//[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

MyVector v4("input.dat");
//v4.pushRear(v3);
v4.print();
// [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]


}