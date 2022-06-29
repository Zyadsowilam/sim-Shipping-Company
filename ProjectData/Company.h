#pragma once

#include <iostream>
#include <fstream>
#include "LinkedQueue.h"
#include "LinkedList.h"
#include "NormWaitList.h"
#include "PriorityQueue.h"
#include "Time.h" 
#include "Cargo.h"
#include "Truck.h"
#include "Events.h"

class UI;
class Time;

class Company
{

	//Data Members for simulation
	bool Simulationdone;
	UI* pUI;
	Time CurrentTime;
	int MaxW;
	int AutoP;
	int J;
	bool WorkingHours;


	//Lists
	QueueP <Cargo*> CargoWaitingVIP;

	LinkedQueue <Cargo*> CargoWaitingSpecial;

	NormWaitList CargoWaitingNormal;

	LinkedQueue <Cargo*> CargoDeliveredVIP;
	LinkedQueue <Cargo*> CargoDeliveredSpecial;
	LinkedQueue <Cargo*> CargoDeliveredNormal;

	LinkedQueue <Events*> EventsList;

	LinkedQueue <Truck*> TrucksAvailableVIP;
	LinkedQueue <Truck*> TrucksAvailableSpecial;
	LinkedQueue <Truck*> TrucksAvailableNormal;

	QueueP <Truck*> TrucksLoading;
	QueueP <Truck*> TrucksMoving;

	LinkedQueue <Truck*> TrucksMaintenanceVIP;
	LinkedQueue <Truck*> TrucksMaintenanceSpecial;
	LinkedQueue <Truck*> TrucksMaintenanceNormal;

	//Data Members for Output
	int PromotedCargosCount;
	

public:
	void Simulation();
	bool Endcondition();
	void ExecuteEvent();
	bool MoveCargo();
	bool FileLoading(string Filename);
	bool CancelCargo(int key);
	bool PromoteCargo(int key, int em);
	void PrepareCargo(char TYP, Cargo* pCargo);
	void AutoPromote();
	int PrintCountWaiting();
	int PrintCountLoading();
	int PrintCountAvailable();
	int PrintCountMoving();
	int PrintCountMaintenance();
	int PrintCountDelivered();

	void PrintCWN();
	void PrintCWS();
	void PrintCWV();

	void PrintCDV();
	void PrintCDS();
	void PrintCDN();

	void PrintEvents();

	void PrintTAV();
	void PrintTAS();
	void PrintTAN();

	void PrintTrucksL();
	void PrintTrucksM();

	void PrintTMV();
	void PrintTMS();
	void PrintTMN();

	


	~Company();
	Company();



};
