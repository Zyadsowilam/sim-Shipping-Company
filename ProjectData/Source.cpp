#include <iostream>
using namespace std;
#include "PriorityQueue.h"
#include "LinkedQueue.h"
#include "Company.h"
#include <string>
#include "UI.h"
#include "LinkedList.h";


ostream& operator<<(ostream& os, Cargo* cargo)
{
	os << cargo->getID();
	return os;
}

ostream& operator<<(ostream& os, Truck* truck)
{
	os << truck->getID();
	return os;
}





int main() 
{
	//Initialization of company
	Company sample;

	//Executes simulation
	sample.Simulation();

	system("pause");
}