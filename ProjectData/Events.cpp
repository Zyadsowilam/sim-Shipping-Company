#include "Events.h"
#include "Company.h"
void Events::execute(Company* company) {
}
Events::Events() 
{

}
void Events::setET(Time et) {
	ET = et;
}
void Events::setID(int id) {
	ID = id;
}
Time Events::getET() {
	return ET;
}
int Events::getID() {
	return ID;
}
Events::~Events() {

}

