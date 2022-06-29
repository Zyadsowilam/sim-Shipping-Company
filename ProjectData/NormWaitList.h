#pragma once

#include "LinkedList.h"
#include "Cargo.h"


class NormWaitList : public LinkedList<Cargo*>
{
public:
	bool Find(int Key, Cargo* & buffer)
	{
		if (count == 0)
			return false;
		Node<Cargo *>* B = Head;
		Node<Cargo *>* F = Head->getNext();
		if (B->getItem()->getID() == Key)
		{
			buffer = B->getItem();
			Head = F;
			delete B;
			count--;
			return true;

		}

		while (F)
		{
			if (F->getItem()->getID() == Key)
			{
				B->setNext(F->getNext());
				buffer = F->getItem();
				delete F;
				count--;
				return true;
			}
			B = B->getNext();
			F = F->getNext();
		}
		return false;
	}
};

