#include "PreperationEvent.h"
#include "Company.h"
#include "Time.h"
PreperationEvent::PreperationEvent()
{
}
void PreperationEvent::setDIST(int d) {
	DIST = d;
}
void PreperationEvent::setLT(int l) {
	LT = l;
}
void PreperationEvent::setTYP(char typ) {
	TYP = typ;
}
void PreperationEvent::setCost(int c) {
	Cost = c;
}
int PreperationEvent::getDIST() {
	return DIST;
}
char PreperationEvent::getTYP() {
	return TYP;
}
int PreperationEvent::getLT() {
	return LT;
}
int PreperationEvent::getCost() {
	return Cost;
}
PreperationEvent::~PreperationEvent() {

}

void PreperationEvent::execute(Company* company)
{
	//Create new cargo based on event parameters
	Cargo* pCargo = new Cargo(ET, ID, DIST, LT, Cost, TYP);
	

	//send to company to insert in appropriate list
	company->PrepareCargo(TYP, pCargo);

	//Deallocate event since it was alloated dynamically
	delete this;

}

void PreperationEvent::LoadEvent(ifstream& inputFile)
{
	//initializations
	int day, hour, ID, CargoDistance, LoadTime, CargoCost;
	char CargoType, buffer;

	//reading input
	inputFile >> CargoType >> day >> buffer >> hour >> ID >> CargoDistance >> LoadTime >> CargoCost;
	Time ET(day, hour);
	//setting data members
	setTYP(CargoType);
	setET(ET);
	setID(ID);
	setDIST(CargoDistance);
	setLT(LoadTime);
	setCost(CargoCost);

}

