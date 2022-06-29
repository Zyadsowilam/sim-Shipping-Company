#include "CancellationEvent.h"
#include "Company.h"

CancellationEvent::CancellationEvent()
{

}

void CancellationEvent::execute(Company* company)
{
	company->CancelCargo(ID);

	delete this;
}


void CancellationEvent::LoadEvent(ifstream& inputFile)
{
	int day, hour, ID;
	char buffer;
	inputFile >> day >> buffer >> hour >> ID;
	Time ET(day, hour);
	setET(ET);
	setID(ID);

}

CancellationEvent::~CancellationEvent()
{

}
