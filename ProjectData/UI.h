#pragma once
#include <iostream>
#include "Company.h"
using namespace std;




class UI
{
public:

	void printint(int in)
	{
		cout << in;
	}

	void printHour(Company* sample,Time CurrentTime)
	{
		//Printinf first line
		cout << "Current Time (Day:Hour):" << CurrentTime.getDay() << ":" << CurrentTime.getHour() <<endl;
		
		//Printing second line
		cout << sample->PrintCountWaiting() << " Waiting Cargos: [";
		sample->PrintCWN();
		cout << "] (";

		sample->PrintCWS();
		cout << ") {";

		sample->PrintCWV();
		cout << "}" << endl;

		printdashedline();

		//Printing third line
		cout << sample->PrintCountLoading();
		cout << " Loading Trucks: ";
		sample->PrintTrucksL();
		cout << endl;

		printdashedline();

		//Printing fourth line
		cout << sample->PrintCountAvailable();
		cout << " Empty Trucks: [";
		sample->PrintTAN();
		cout << "] (";

		sample->PrintTAS();
		cout << ") {";

		sample->PrintTAV();
		cout << "}" << endl;

		printdashedline();

		//Printing Fifth line
		cout << sample->PrintCountMoving();
		cout << " Moving Cargos: ";
		sample->PrintTrucksM();
		cout << endl;
		printdashedline();

		//Printing Sixth line
		cout << sample->PrintCountMaintenance();
		cout << " In-Checkup Trucks: [";
		sample->PrintTMN();
		cout << "] (";

		sample->PrintTMS();
		cout << ") {";

		sample->PrintTMV();
		cout << "}" << endl;

		printdashedline();

		//Printing Last Line
		cout << sample->PrintCountDelivered();
		cout << " Delivered Cargos: [";
		sample->PrintCDN();
		cout << "] (";

		sample->PrintCDS();
		cout << ") {";

		sample->PrintCDV();
		cout << "}" << endl;

	}

	void printstring(string msg)
	{
		cout << msg;

	}

	void WaitForInput()
	{
		cin.get();
	}

	string getfilename()
	{
		string buffer;
		cin >> buffer;
		cin.ignore();
		return buffer;

	}

	void printdashedline()
	{
		cout << "- -----------------------------"  << endl;

	}
	string choosemode()
	{
		string buffer;
		bool valid = false;
		while (!valid)
		{
			cout << "Enter Mode";
			cin >> buffer;
			if (buffer == "interactive" || buffer == "silent" || buffer == "step by step")
				valid = true;
			else
				cout << "Unsupported Mode, Supported modes are 'interactive', 'silent' and 'step by step'";

		}
		return buffer;

	}

};

