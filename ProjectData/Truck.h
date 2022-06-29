#pragma once
#include <iostream>
#include "PriorityQueue.h"
#include "LinkedQueue.h"
#include "Cargo.h"
class Truck
{
private:
	static int counter;
	int ID;
	//Data Members loaded from input file
	char type;
	int TC;
	int checkup;
	int speed;
	//Data Members used in simulation function(phase 2)
	bool MaxWait;
	QueueP <Cargo*> StoredCargo;
	int DeliveriesCount;
	int DeliveredCargoCount;
	Time exitTime;
	float interval;
	LinkedQueue <Cargo*> LoadingCargo;
	bool Truckempty;
	int ActiveTime;
	//exit time is used for moving or loading priority queue

public:

	friend	ostream& operator<<(ostream& os, Truck* truck);



	Truck()
	{
		MaxWait = false;
		Truckempty = false;
		DeliveredCargoCount = 0;
		DeliveriesCount = 0;
		counter++;
		ID = counter;
		type = 'X';
		TC = 0;
		checkup = 0;
		speed = 0;
		interval = 0;
		
	}


	Truck(char t, int tc, int check, int s, float i)
	{
		MaxWait = false;
		Truckempty = false;
		DeliveredCargoCount = 0;
		DeliveriesCount = 0;
		counter++;
		ID = counter;
		type = t;
		TC = tc;
		checkup = check;
		speed = s;
		interval = i;
	}



	int getID()
	{
		return ID;
	}

	int getCapacity()
	{
		return TC;
	}


};