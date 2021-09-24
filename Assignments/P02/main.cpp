/**
*
*  Author:           Alex Ryan
*  Title:            Linked List Example
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
#include <array>

using namespace std;

// Node for our linked list
struct node {
  int data;  // data value (could be a lot more values)

  node* next;  // we always need a "link" in a linked list
  node* prev;

  node(int x) {  // cunstructor to make adding values easy
    data = x;
    next = NULL;
    prev = NULL;
  }
};

/**
 * @brief Load array with values from a file
 *
 * @param string filename
 * @param int*& arr
 * @param int& size
 */
void loadArr(string filename, int*& arr, int& size) {
  ifstream fin;         // stream reference
                        //
  fin.open(filename);   // open the file
                        //
  fin >> size;          // get first value which contains
                        // number of remaining values in file
                        //
  arr = new int[size];  // allocate new array of correct size
                        //
  int i = 0;            // need an array index for our while loop
                        //
  // Can also use for loop since we know the exact count in file.
  // eof = end of file flag
  // `!fin.eof()` evaulates to true when we hit end of file.
  while (!fin.eof()) {
    fin >> arr[i];  // read file value straight into array
                    // at index i
    i++;            // increment array index
  }
}

/**
 * @brief Prints an array
 *
 * @param int arr
 * @param int size
 *
 * @returns void
 */
void printArr(int* arr, int ArrSize) {
  for (int i = 0; i < ArrSize; i++) {
    cout << "[" << arr[i] << "]";
  }
  cout << "\n";
}

/**
 * Class Name
 * 
 * Description:
 *      Creates a list of ints with overloaded operators 
 * 
 * Public Methods:
 *      MyVector()
 *      MyVector(int A[], int Arrsize)
 *      MyVector(const MyVector& other)     
 *      int& operator[](int index)
 *      MyVector operator+(MyVector const& other)
 *      MyVector operator-(MyVector const& other)
 *      MyVector operator*(MyVector const& other)
 *      MyVector operator/(MyVector const& other)
 *      bool operator==(MyVector const& other)
 *      MyVector operator=(const MyVector& other)
 *      void push_rear(int x)
 *      friend fstream& operator<<(fstream& os, const MyVector& other)
 *      friend ostream& operator<<(ostream& os, const MyVector& other)
 *      void push_rear(int x)
 *
 * Private Methods:
 *      node* head
 *      node* tail
 *      int size
 * 
 * Usage: 
 * 
 *      - examples of how
 *      - to use your class 
 *      
 */

class MyVector {
 private:
  node* head;  // base pointer of list
  node* tail;
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
    head = NULL;  // NULL = zeros
                  // and zeros imply empty
    size=0;
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
  MyVector(int A[], int Arrsize) {
    head = NULL;  // NULL = zeros
                  // and zeros imply empty
    for (int i = 0; i < Arrsize; i++) {
      push_rear(A[i]);
    }
     size=0;
  }

    /**
     * Public : MyVector(const MyVector& other)
     * 
     * Description:
     *      Implementation of a copy constructor
     * 
     * Params:
     *      const MyVector& other  :  array of integers
     * 
     * Returns:
     *      None
     */

  MyVector(const MyVector& other) {
    head = tail = nullptr;
    size=0;

    node* otherHead = other.head;  // reference other object

    while (otherHead) {
      this->push_rear(otherHead->data);
      otherHead = otherHead->next;
    }
  }

    /**
     * Public : int& operator[](int index)
     * 
     * Description:
     *      overloads the [] so that you can retrieve data @ index
     * 
     * Params:
     *      int index 
     * 
     * Returns:
     *      int data the data in the index
     */

  int& operator[](int index) {
    node* travel = head;
    int currentLoc = 0;
    while (index--) {
      travel = travel->next;
    }
    return travel->data;
  }

    /**
     * Public : MyVector operator+(MyVector const& other)
     * 
     * Description:
     *      overloads the + operator to add two lists
     * 
     * Params:
     *      MyVector const& other
     * 
     * Returns:
     *      MyVector
     */

  MyVector operator+(MyVector const& other) {
    // new list
    MyVector newVector;  // create a new vector here.

    node* thisHead = head;         // get copy of the head of list
    node* otherHead = other.head;  // same for other

    if (this->size < other.size) {  // check to see which list is longer
      for (int i = 0; i < this->size; i++) {  // runs if lhs is shorter
        newVector.push_rear(thisHead->data +otherHead->data);  // push the result to the end of the list
        otherHead = otherHead->next;  // walk down the list
        thisHead = thisHead->next;
        //newVector.size++;
      }
      for (int i = other.size - this->size; i > 0;
           i--) {  // Run the length of rhs and just throw the remaining values
                   // into new
        newVector.push_rear(otherHead->data);
        otherHead = otherHead->next;
      }

    } else if (this->size >= other.size) {  // in the case lhs is longer
      while (otherHead != nullptr) {
        newVector.push_rear(thisHead->data + otherHead->data);
        otherHead = otherHead->next;
        thisHead = thisHead->next;
        //newVector.size++;
      }
      while (thisHead != nullptr) {
        newVector.push_rear(thisHead->data);
        thisHead = thisHead->next;
        //newVector.size++;
      }
    }
    // remaining nodes
    return newVector;
  }

    /**
     * Public : MyVector operator-(MyVector const& other)
     * 
     * Description:
     *      overloads the - operator to subtract one list from another
     * 
     * Params:
     *      MyVector const& other
     * 
     * Returns:
     *      MyVector
     */

  MyVector operator-(MyVector const& other) {
    MyVector newVector;

    node* thisHead = head;
    node* otherHead = other.head;
    
    
    while (thisHead && otherHead) {       //runs till either == null
      newVector.push_rear(thisHead->data - otherHead->data);
      otherHead = otherHead->next;
      thisHead = thisHead->next;
    }
    while(thisHead) {
      newVector.push_rear(thisHead->data);
      thisHead = thisHead->next;
    }
    while(otherHead) {
      newVector.push_rear(otherHead->data);
      otherHead = otherHead->next;
    }
    
    // remaining nodes
    return newVector;
  }

    /**
     * Public : MyVector operator*(MyVector const& other)
     * 
     * Description:
     *      overloads the * to multiply two MyVectors
     * 
     * Params:
     *      MyVector const& other
     * 
     * Returns:
     *      MyVector
     */

  MyVector operator*(MyVector const& other) {
     MyVector newVector;

    node* thisHead = head;
    node* otherHead = other.head;
    
    while (thisHead && otherHead) {
      newVector.push_rear(thisHead->data * otherHead->data);
      otherHead = otherHead->next;
      thisHead = thisHead->next;
    }
    while(thisHead) {
      newVector.push_rear(thisHead->data);
      thisHead = thisHead->next;
    }
    while(otherHead) {
      newVector.push_rear(otherHead->data);
      otherHead = otherHead->next;
    }

    return newVector;
  }

    /** 
     * Public : MyVector operator/(MyVector const& other)
     * 
     * Description:
     *      overloads the / operator to divide the values of two lists
     * 
     * Params:
     *      MyVector const& other
     * 
     * Returns:
     *      MyVector
     */

  MyVector operator/(MyVector const& other) {
    MyVector newVector;

    node* thisHead = head;
    node* otherHead = other.head;

    while (thisHead && otherHead) {
      if (otherHead->data !=0 ) {
        newVector.push_rear(thisHead->data / otherHead->data);
        otherHead = otherHead->next;
        thisHead = thisHead->next;
      }
      else {
        newVector.push_rear(thisHead->data);
        otherHead = otherHead->next;
        thisHead = thisHead->next;
      }
    }
    while(thisHead) {
      newVector.push_rear(thisHead->data);
      thisHead = thisHead->next;
    }
    while(otherHead) {
      newVector.push_rear(otherHead->data);
      otherHead = otherHead->next;
    }
    return newVector;
  }

    /**
     * Public : bool operator==(MyVector const& other)
     * 
     * Description:
     *      overloads the == to compare two lists
     * 
     * Params:
     *      int*    :  array of integers
     *      int     :  array size
     * 
     * Returns:
     *      List*   : a pointer to a linked list of integers.
     */

  bool operator==(MyVector const& other) {
    MyVector newVector;

    node* thisHead = head;
    node* otherHead = other.head;
    if (this->size != other.size) {
      return false;
    } else {
      while (thisHead) {
        if (thisHead->data != otherHead->data) {
          return false;
        } else if (!thisHead->next || !otherHead->next) {
          return true;
        } else {
          otherHead = otherHead->next;
          thisHead = thisHead->next;
        }
      }
    }
    return false;
  }

    /**
     * Public : MyVector operator=(const MyVector& other)
     * 
     * Description:
     *      overloads = operator to make one list equal to another
     * 
     * Params:
     *      const MyVector& other
     * 
     * Returns:
     *      MyVector
     */

  MyVector operator=(const MyVector& other) {

    if(this == &other){   //checks for self assignment
      return *this;
    }

    node* curr;
    node* prev;

    curr = prev = this->head;

    while(curr){
      prev = curr;
      curr = curr->next;
      delete prev;
    }

    this->head = nullptr;

    node* otherHead = other.head;  // reference other object

    while (otherHead) {
      this->push_rear(otherHead->data);
      otherHead = otherHead->next;
    }
    
    return *this;
  }

    /**
     * Public : void push_rear(int x)
     * 
     * Description:
     *      adds a value to the end of list
     * 
     * Params:
     *      int x : the value you wish to add to the end of the list
     * 
     * Returns:
     *      void
     */

  void push_rear(int x) {
    node* tempPtr = new node(x); //Creates a new node to add to the end of the list

    if (!head) {
      head = tail = tempPtr;
    } else {
      tail->next = tempPtr;
      tail = tempPtr;
    }
    size++;
  }

    /**
     * Public : friend fstream& operator<<(fstream& os, const MyVector& other)
     * 
     * Description:
     *      prints to an outfile
     * 
     * Params:
     *      fstream& os, const MyVector& other
     * 
     * Returns:
     *      fstream&
     */

  friend fstream& operator<<(fstream& os, const MyVector& other) {
    node* temp = other.head;  // temp pointer copies head

    while (temp) {  // this loops until temp is NULL
                    // same as `while(temp != NULL)`

      os << temp->data;  // print data from node
      if (temp->next) {
        os << "->";
      }
      temp = temp->next;  // move to next node
    }
    os << endl;
    return os;
  }

    /**
     * Public : friend ostream& operator<<(ostream& os, const MyVector& other)
     * 
     * Description:
     *      Prints to the console
     * 
     * Params:
     *      ostream& os, const MyVector& other
     * 
     * Returns:
     *      ostream&
     */

  friend ostream& operator<<(ostream& os, const MyVector& other) {
    node* temp = other.head;  // temp pointer copies head

    while (temp) {  // this loops until temp is NULL
                    // same as `while(temp != NULL)`

      os << temp->data;  // print data from node
      if (temp->next) {
        os << "->";
      }
      temp = temp->next;  // move to next node
    }
    os << endl;
    return os;
  }

/**
     * Public : void print()
     * 
     * Description:
     *      prints an array
     * 
     * Params:
     *      none
     * 
     * Returns:
     *      void
     */

  void print() {
    node* temp = head;  // temp pointer copies head

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

  int getSize() { return size; }

  ~MyVector() {}
};

int main() {

int a1[] = { 1, 2, 3, 4, 5 };
int a2[] = { 10, 20, 30 };

MyVector v1(a1, 5);
MyVector v2(a2, 3);

ofstream fout;
fout.open("output.txt");

cout << v1[2] << endl;
// writes out 3

v1[4] = 9;
// v1 now = [1,2,3,4,9]

cout << v1 << endl;
// writes out [1,2,3,4,9] to console.

fout << v1 << endl;
// writes out [1,2,3,4,9] to your output file.

MyVector v3 = v1 + v2;
cout << v3 << endl;
// writes out [11,22,33,4,9] to console.

v3 = v1 - v2;
cout << v3 << endl;
// writes out [-9,-18,-27,4,9] to console.

v3 = v2 - v1;
cout << v3 << endl;
// writes out [9,18,27,4,9] to console.

v3 = v2 * v1;
cout << v3 << endl;
// writes out [10,40,90,4,9] to console.

v3 = v1 * v2;
cout << v3 << endl;
// writes out [10,40,90,4,9] to console.

v3 = v1 / v2;
cout << v3 << endl;
// writes out [0,0,0,4,9] to console.

v3 = v2 / v1;
cout << v3 << endl;
// writes out [10,10,10,4,9] to console.

cout << (v2 == v1) << endl;
// writes 0 to console (false) .

MyVector v4 = v1;
cout << (v4 == v1) << endl;
// writes 1 to console (true) .


}
