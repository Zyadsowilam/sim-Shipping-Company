#pragma once

#include "Time.h"
#include <fstream>

using namespace std;
class Company;
class Events
{
protected:

	Time ET;
	int ID;
public:
	Events();
	virtual void execute(Company* company) = 0;
	virtual void LoadEvent(ifstream& inputFile) = 0;
	void setID(int id);
	void setET(Time et);
	int getID();
	Time getET();
	~Events();
};

