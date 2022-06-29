#pragma once
#include "Events.h"

class PreperationEvent :
    public Events
{
private:
    char TYP;
    int DIST;
    int LT;
    int Cost;
public:
    PreperationEvent();
    void execute(Company* company);
    void setDIST(int d);
    void setLT(int l);
    void setTYP(char typ);
    void setCost(int c);
    int getDIST();
    int getLT();
    char getTYP();
    int getCost();
    void LoadEvent(ifstream& inputFile);
    ~PreperationEvent();
};

