#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"

template <typename T>
class LinkedList
{
protected:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	int count;
	Node<T>* backPtr;
public:


	LinkedList()
	{
		Head = nullptr;
		backPtr = nullptr;
		count = 0;
	}
	int GetCount() {
		return count;
	}
	bool ReturnFirst(T& frntEntry)
	{
		Node<T>* temp = Head;
		if (!Head)
			return false;
		frntEntry = Head->getItem();
		Head = Head->getNext();
		delete temp;
		count--;
		if (!Head)
			backPtr = nullptr;
		return true;
	}

	bool PeakFirst(T& frntEntry)
	{
		Node<T>* temp = Head;
		if (!Head)
			return false;
		frntEntry = Head->getItem();
		return true;

	}

	bool isEmpty()
	{
		return (Head == nullptr);
	}


	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{

		Node<T>* p = Head;

		for (int i = 0; i < count; i++)
		{
			cout << p->getItem();
			if (i != (count - 1))
				cout << ',';

			p = p->getNext();
		}

	}

	///////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
		if (!Head)
			backPtr = nullptr;
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data) {
		Node<T>* newNodePtr = new Node<T>(data);
		// Insert the new node
		if (isEmpty())    //special case if this is the first node to insert
			Head = newNodePtr; // The queue is empty
		else
			backPtr->setNext(newNodePtr); // The queue was not empty

		backPtr = newNodePtr; // New node is the last node now
		count++;
	}

	//[2]Find 
	//searches for a given value in the list, returns true if found and removes it; false otherwise.
	bool Find(int Key,T& buffer)
	{
		return false;
	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value);

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst();


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast();

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(int Key, T& buffer);

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value);

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(const LinkedList& L);

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse();

};

#endif	
