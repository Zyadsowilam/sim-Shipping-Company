#include "Company.h"

#include "UI.h"
#include"Company.h"
#include "CancellationEvent.h"
#include "PreperationEvent.h"
#include "PromotionEvent.h"
#include "Cargo.h"
#include "Truck.h"


Company::Company()
{
	pUI = new UI;
	PromotedCargosCount = 0;
	Simulationdone = false;
	WorkingHours = false;

}

void Company::AutoPromote()
{

	Cargo* bufferC;
	bool check = CargoWaitingNormal.PeakFirst(bufferC);
	if (check)
	{
		while (AutoP <= bufferC->GetWaitTimeDays(CurrentTime))
		{

			//remove cargo from normal
			CargoWaitingNormal.ReturnFirst(bufferC);

			//Add cargo to VIP
			CargoWaitingVIP.Push(bufferC, 1);

			//PromotedCargosCount++; (phase 2)

			//check for next cargo
			CargoWaitingNormal.PeakFirst(bufferC);

			//wont continue checking if list is empty
			check = CargoWaitingNormal.isEmpty();
			if (check)
			{
				return;
			}
			
		}

	}
	return;

}

void Company::Simulation()
{
	//Gets filename and loads it
	string filename = pUI->getfilename();
	bool buffer = true;
	buffer = FileLoading(filename);
	if (!buffer)
	{
		pUI->printstring("error loading file");
		return;
	}
	//TODO: Choose mode(phase 2)
	//string mode = sampleUI.choosemode();
		

	//initialization of counter for move cargo
	int counter = 0;
	
	//As long as end condition is not met simulation will continue
	while (!Endcondition())
	{
		//increments time for event time
		CurrentTime.IncrementTime();
		//increments counter used for moving cargo
		counter++;

		//check if there is an event to execute, if any are found they are executed
		ExecuteEvent();

		//checks if any cargo(s) fuflfilled auto promotion condition, if any have they are promoted to VIP
		//AutoPromote();

		//TODO: Assign Cargo to truck then move cargos/trucks through their respective phases (phase 2)

		//every 5 hours will move cargo
		if (counter >= 5)
		{
			MoveCargo();
			counter = 0;

		}
		//TODO: collect any needed info (phase 2)

		//Print Interface
		pUI->printHour(this, CurrentTime);

		//Since phase 1, interface mode is assumed and program will wait for use to press "enter"
		pUI->WaitForInput();
		
	}

	return;
	//TODO: Produce output file(phase 2)



}

bool Company::Endcondition()
{
	if (EventsList.GetCount() == 0 && CargoWaitingVIP.GetCount() == 0 && CargoWaitingSpecial.GetCount() == 0 && CargoWaitingNormal.GetCount() == 0)
	{
		Simulationdone = true;
		return true;

	}
	return false;
		
	//TODO: Add checks for trucks by checking none are loading, moving or in maintenace (phase 2)
	// return Simulationdone;
}

void Company::ExecuteEvent()
{
	Events* buffer;
	bool check = EventsList.peek(buffer);

	if (check)
	{
		while (CurrentTime.TimeEqual(buffer->getET()))
		{
			//remove event from event list
			EventsList.dequeue(buffer);

			//execute event
			buffer->execute(this);

			//check for next event
			EventsList.peek(buffer);

			//if list is empty wont continue checking
			check = EventsList.isEmpty();
			if (check)
			{
				return;
			}
		}

	}
	return;
}

bool Company::MoveCargo()
{

	Cargo* buffer;
	bool check;
	//Delivering VIP cargo
	if (CargoWaitingVIP.GetCount() > 0)
	{
		CargoDeliveredVIP.enqueue(CargoWaitingVIP.Pop());
	}
	
	//Delivering Special Cargo
	check = CargoWaitingSpecial.dequeue(buffer);
	if (check)
	{
		CargoDeliveredSpecial.enqueue(buffer);
	}
	//Delivering Normal Cargo
	check = CargoWaitingNormal.ReturnFirst(buffer);
	if (check)
	{
		CargoDeliveredNormal.enqueue(buffer);
	}
	return check;

}

bool Company::FileLoading(string Filename)
{
	ifstream inputFile;
	inputFile.open(Filename + ".txt", ios::in);
	if (!inputFile.is_open())
	{
		pUI->printstring("Failed to open file, aborting loading");
		return false;

	}

	//initializations
	int countNormalTrucks, countSpecialTrucks,countVIPTrucks, countEvents;
	int NormalSpeed, SpecialSpeed, VIPSpeed;
	int CapacityNormal, CapacitySpecial, CapacityVIP;
	int CheckupNormal, CheckupSpecial, CheckupVIP, j;
	int AutoPromotion, MaxWait;
	char eventtype;

	//First line in input file
	inputFile >> countNormalTrucks >> countSpecialTrucks >> countVIPTrucks;
	//Second line in input file
	inputFile >> NormalSpeed >> SpecialSpeed >> VIPSpeed;
	//Third line in input file
	inputFile >> CapacityNormal >> CapacitySpecial >> CapacityVIP;
	//Fourth line in input file
	inputFile >> CheckupNormal >> CheckupSpecial >> CheckupVIP >> j;
	//Fifth line in input file
	inputFile >> AutoPromotion >> MaxWait;
	J = j;
	AutoP = AutoPromotion;
	MaxW = MaxWait;


	//still need to add data members for trucks and company

	for (int i = 0; i <countNormalTrucks; i++)
	{
		//send normal speed, checkup, type, capacity
		Truck* pTrucks;
		pTrucks = new Truck('N', CapacityNormal, CheckupNormal, NormalSpeed, 1);
		TrucksAvailableNormal.enqueue(pTrucks);
	}

	for (int i = 0; i < countSpecialTrucks; i++)
	{
		//send special speed, checkup, type, capacity
		Truck* pTrucks;
		pTrucks = new Truck('S', CapacitySpecial, CheckupSpecial, SpecialSpeed, 1);
		TrucksAvailableSpecial.enqueue(pTrucks);
	}


	for (int i = 0; i < countVIPTrucks; i++)
	{
		//send VIP speed, checkup, type, capacity
		Truck* pTrucks;
		pTrucks = new Truck('V', CapacityVIP, CheckupVIP, VIPSpeed, 1);
		TrucksAvailableVIP.enqueue(pTrucks);
		
	}

	//Sixth Line in input file
	inputFile >> countEvents;

	//Loop to load all events
	for (int i = 0; i < countEvents; i++)
	{
		inputFile >> eventtype;
		//Loading based on event type then enque into events list
		if (eventtype == 'R')
		{
			Events* pEvents = new PreperationEvent;
			pEvents->LoadEvent(inputFile);
			EventsList.enqueue(pEvents);

		}
		else if (eventtype == 'X')
		{
			Events* pEvents = new CancellationEvent;
			pEvents->LoadEvent(inputFile);
			EventsList.enqueue(pEvents);

		}
		else if (eventtype == 'P')
		{
			Events* pEvents = new PromotionEvent;
			pEvents->LoadEvent(inputFile);
			EventsList.enqueue(pEvents);

		}
		
	}

	return true;

}

bool Company::CancelCargo(int key)
{
	bool check;
	Cargo* buffer;
	//searches for cargo in linked list and if found removes it and returns it
	check = CargoWaitingNormal.Find(key, buffer);

	//Completely Removes Cargo if it was found
	if (check)
	{
		delete buffer;
	}
	return check;
}

bool Company::PromoteCargo(int key, int em)
{
	bool check;
	Cargo* buffer;
	//searches for cargo in linked list and if found removes it and returns it
	check = CargoWaitingNormal.Find(key, buffer);

	//Adds cargo to VIP list if it was found
	if (check)
	{
		buffer->AddMoney(em);
		CargoWaitingVIP.Push(buffer, 1);

	}
	return check;
}

void  Company::PrepareCargo(char TYP, Cargo* pCargo)
{
	//insert in waiting list based on cargo type
	switch (TYP) {
	case 'N': {
		CargoWaitingNormal.InsertEnd(pCargo);
		break;
	}
	case 'S': {
		CargoWaitingSpecial.enqueue(pCargo);
		break;
	}
	case 'V': {
		CargoWaitingVIP.Push(pCargo, 1);
		break;
	}
	default:
		break;
	}

}




Company::~Company()
{

	//deallocation of all trucks/cargos allocated throughout the simulation 
	//canceled cargos/events are deallocated at execution of event
	Cargo* Cbuffer;
	Truck* Tbuffer;
	while (TrucksAvailableVIP.dequeue(Tbuffer))
	{
		delete Tbuffer;
	}

	while (TrucksAvailableSpecial.dequeue(Tbuffer))
	{
		delete Tbuffer;
	}

	while (TrucksAvailableNormal.dequeue(Tbuffer))
	{
		delete Tbuffer;
	}

	while (CargoDeliveredVIP.dequeue(Cbuffer))
	{
		delete Cbuffer;
	}

	while (CargoDeliveredSpecial.dequeue(Cbuffer))
	{
		delete Cbuffer;
	}

	while (CargoDeliveredNormal.dequeue(Cbuffer))
	{
		delete Cbuffer;
	}

	delete pUI;

}



//Printing Lists Functions


void Company::PrintCWN()
{
	CargoWaitingNormal.PrintList();
	return;
}

void Company::PrintCWS()
{
	CargoWaitingSpecial.Print();
	return;
}

void Company::PrintCWV()
{
	CargoWaitingVIP.Print();
	return;
}



void Company::PrintCDN()
{
	CargoDeliveredNormal.Print();
	return;
}

void Company::PrintCDS()
{
	CargoDeliveredSpecial.Print();
	return;
}

void Company::PrintCDV()
{
	CargoDeliveredVIP.Print();
	return;
}



void Company::PrintEvents()
{
	EventsList.Print();
	return;
}



void Company::PrintTAN()
{
	TrucksAvailableNormal.Print();
	return;
}

void Company::PrintTAS()
{
	TrucksAvailableSpecial.Print();
	return;
}

void Company::PrintTAV()
{
	TrucksAvailableVIP.Print();
	return;
}




void Company::PrintTrucksL()
{
	TrucksLoading.Print();
	return;
}


void Company::PrintTrucksM()
{
	TrucksMoving.Print();
	return;
}




void Company::PrintTMN()
{
	TrucksMaintenanceNormal.Print();
	return;
}


void Company::PrintTMS()
{
	TrucksMaintenanceSpecial.Print();
	return;
}

void Company::PrintTMV()
{
	TrucksMaintenanceVIP.Print();
	return;
}

//Getters for count used ONLY for printing

int Company::PrintCountWaiting()
{
	//second line in interface
	TrucksLoading.GetCount();
	return (CargoWaitingNormal.GetCount() + CargoWaitingSpecial.GetCount() + CargoWaitingVIP.GetCount());
}

int Company::PrintCountLoading()
{
	//third line in interface

	return (TrucksLoading.GetCount());
}

int Company::PrintCountAvailable()
{
	//fourth line in interface

	return (TrucksAvailableVIP.GetCount() + TrucksAvailableSpecial.GetCount() + TrucksAvailableNormal.GetCount());
}

int Company::PrintCountMoving()
{
	//fifth line in interface

	return (TrucksMoving.GetCount());
}

int Company::PrintCountMaintenance()
{
	//sixth line in interface

	return (TrucksMaintenanceVIP.GetCount() + TrucksMaintenanceSpecial.GetCount() + TrucksMaintenanceNormal.GetCount());
}

int Company::PrintCountDelivered()
{
	//last line in interface

	return (CargoDeliveredNormal.GetCount() + CargoDeliveredSpecial.GetCount() + CargoDeliveredVIP.GetCount());
}



