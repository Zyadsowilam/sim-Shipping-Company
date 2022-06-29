#pragma once
#include <iostream>
#include <new>
using namespace std;

// Queue with priority of type T
template <typename T>
class QueueP
{
private:
    T* A; // dynamic array of items of type T
    int* P; // array of priorities
    int count; // number of items in the queue

public:
    // default constructor
    QueueP() { count = 0; }

    // copy constructor
    QueueP(const QueueP& _Q)
    {
        try {
            // attempt to allocate memory
            A = new T[_Q.count];
            P = new int[_Q.count];
        }
        catch (bad_alloc e)
        {
            // if memory is not allocated then process the error
            cout << e.what() << endl;
            count = 0;
            return;
        }

        // copy _Q => *this
        count = _Q.count;

        // copying data elementwise
        for (int i = 0; i < count; i++)
            A[i] = _Q.A[i];

        for (int i = 0; i < count; i++)
            P[i] = _Q.P[i];
    }

    // destructor
    ~QueueP()
    {
        if (count > 0)
        {
            delete[] A;
            delete[] P;
        }
    }

    // copy operator - to avoid bitwise copying
    QueueP operator=(const QueueP& _Q);

    // function that adds a new item to the queue
    void Push(T item, int priority);

    // function pulling the first item from the queue
    T Pop();

    // queue clearing
    void Clear()
    {
        if (count > 0)
        {
            delete[] A;
            delete[] P;
            count = 0;
        }
    }

    int GetCount()
    {
        return count;
    }

    // function, which display the queue
    void Print();

};

//end of class

// copy operator
template <typename T>
QueueP<T> QueueP<T>::operator=(const QueueP& _Q)
{
    // 1. Free memory that was previously allocated for the current object.
    if (count > 0)
    {
        delete[] A;
        delete[] P;
        count = 0;
    }

    // 2. Attempt to allocate a new piece of memory
    try {
        A = new T[_Q.count];
        P = new int[_Q.count];
    }
    catch (bad_alloc e)
    {
        // if no memory is allocated, then exit
        cout << e.what() << endl;
        return *this; // return an empty queue
    }

    // 3. If memory is allocated, then copying *this <= _Q
    count = _Q.count;

    // 4. data Copying loop
    for (int i = 0; i < count; i++)
    {
        A[i] = _Q.A[i];
        P[i] = _Q.P[i];
    }
    return *this;
}

// It adds a new item item to the queue with priority
template <typename T>
void QueueP<T>::Push(T item, int priority)
{
    // 1. Create a new queue array and priority array
    T* A2;
    int* P2;

    try {
        // attempt to allocate memory for new arrays
        A2 = (T*)new T[count + 1];
        P2 = (int*)new int[count + 1];
    }
    catch (bad_alloc e)
    {
        // if memory is not allocated then exit
        cout << e.what() << endl;
        return;
    }

    // 2. Search for pos position in array P according to its priority
    int pos;

    if (count == 0)
        pos = 0;
    else
    {
        pos = 0;
        while (pos < count)
        {
            if (P[pos] < priority) break;
            pos++;
        }
    }

    // 3. Copy data A2<=A; P2<=P
    // using formula P = [0,1,...] + pos+1 + [pos+2,pos+3,...]
    // 3.1. Indices of array with numbers 0..pos
    for (int i = 0; i < pos; i++)
    {
        A2[i] = A[i];
        P2[i] = P[i];
    }

    // 3.2. Add an item at position pos
    A2[pos] = item;
    P2[pos] = priority;

    // 3.3. Items after position pos
    for (int i = pos + 1; i < count + 1; i++)
    {
        A2[i] = A[i - 1];
        P2[i] = P[i - 1];
    }

    // 4. Free memory previously allocated for A and P
    if (count > 0)
    {
        delete[] A;
        delete[] P;
    }

    // 5. Redirect pointers A->A2, P->P2
    A = A2;
    P = P2;

    // 6. Increase the number of items in the queue by 1
    count++;
}

// Function that pulls the first item from the queue
template <typename T>
T QueueP<T>::Pop()
{
    // 1. Checking
    if (count == 0)
        return 0;

    // 2. Declare temporary arrays
    T* A2;
    int* P2;

    // 3. Attempt to allocate memory for A2, P2
    try {
        A2 = new T[count - 1];
        P2 = new int[count - 1];
    }
    catch (bad_alloc e)
    {
        // if no memory is allocated, then return 0 and exit
        cout << e.what() << endl;
        return 0;
    }

    // 4. Remember first item
    T item;
    item = A[0];

    // 5. Copy data from arrays A => A2, P => P2 without the first item
    for (int i = 0; i < count - 1; i++)
    {
        A2[i] = A[i + 1];
        P2[i] = P[i + 1];
    }

    // 6. Free pre-allocated memory for A, P
    if (count > 0)
    {
        delete[] A;
        delete[] P;
    }

    // 7. Correct the number of items in the queue
    count--;

    // 8. Redirect pointers A-> A2, P-> P2
    A = A2;
    P = P2;

    // 9. Return first element of queue
    return item;
}

// Function that displays a queue on the screen
template <typename T>
void QueueP<T>::Print()
{
    if (count == 0) {
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << A[i];
        if (i != (count - 1))
            cout << ',';
    }
}
