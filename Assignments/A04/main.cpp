//////////////////////////////////////////////////////////////////////////////
//
// Author: Alex Ryan
// Email: Alexanderryan133@gmail.com
// Label: A04
// Title: Basic Project Organization 
// Course: 2143 Object Oriented Programming 
// Semester: Fall 2021
//
// Description: 
//  This program creates a class that creates a circular queue that tracks 
//  the front and rear of 
//  the array
//
// Usage:
//  run the file
//////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

//
// CircularArrayQue
// 
// Description:
//      This class implements a circular array based queue with push and pop 
//      method
//
// Public Methods:
//      -CircularArrayQue() 
//      -CircularArrayQue(int size) 
//      -Push(int item) 
//      -Pop() 
//
// Private Methods:
//      void        init
//      bool        Full
//
// Usage:
//      use the constructor to make the desired queue size and use the 
//      push/pop methods add and remove numbers onto the queue
//      

class CircularArrayQue {
private:
    int *Container;     // dynamically allocated array
    int Front;          // tracks the front of the queue
    int Rear;           // tracks the rear of the queue
    int QueSize;        // items in the queue
    int CurrentSize;    // tracks the total size of the array

    ////
    // Private : init
    // 
    // Description: 
    //      initializes the array to be size 0
    //
    // Parameters:
    //      int size: integer of size
    //
    // Returns:
    //      Nothing
    ////

    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }

    ////
    // Private : Full
    // 
    // Description:
    //      checks to see if its full
    //
    // Parameters:
    //      none
    //
    // Returns: 
    //      returns the result of if the queue is full (T/F)
    ////

    bool Full() {
        return CurrentSize == QueSize;
    }

public:
    ////
    // Public : CircularArrayQue
    //
    // Description: 
    //      a default constructor that creates the queue of size 10
    //      
    //  Parameters:
    //      None
    ////
    CircularArrayQue() {
        Container = new int[10];
        init(10);
    }

    ////
    // Public : CircularArrayQue
    //
    // Description: 
    //      an overloaded constructor that takes an int and creates a 
    //      queue of size 'size'
    //
    // Parameters:
    //      int size      
    ////
    CircularArrayQue(int size) {
        Container = new int[size];
        init(size);
    }

    ////
    // Public : Push
    //
    // Description:
    //      a method that accepts an int 'item' that checks to 
    //      see if the queue is full, if the queue is full then it will output
    //      a warning message. Else, the method will place the given parameter 
    //      at the end of the queue and move the rear. Returns nothing
    //      
    // Parameters:
    //      int item
    ////
    void Push(int item) {
        if (!Full()) {
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;
        } else {
            cout << "FULL!!!!" << endl;
        }
    }

    ////
    // Public : Pop
    //
    // Description:
    //      a method that returns the int at the front of the queue, 
    //      removes then moves the front.  
    ////
    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};

ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);
    C1.Push(2);
    C1.Push(3);
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;
}