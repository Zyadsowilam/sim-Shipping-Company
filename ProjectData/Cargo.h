#pragma once

#include "Time.h"

using namespace std; 

class Cargo
{
private:

    Time PreparationTime;
    int ID;
    int CargoDistance;
    int LoadTime;
    float CargoCost;
    char CargoType;
    //For Output
    Time WaitTime;
    int DeliveryTruckID;
    Time CDT;
    
public:

    friend ostream& operator<<(ostream& os, Cargo* cargo);


    Cargo(Time PT, int id, int CargoDis, int LoadT, int CCost, char CType)
    {
        PreparationTime = PT;
        ID = id;
        CargoDistance = CargoDis;
        LoadTime = LoadT;
        CargoCost = CCost;
        CargoType = CType;

    }

    void AddMoney(int extracost)
    {
        CargoCost = CargoCost + extracost;
        CargoType = 'V';

    }

    int getID()
    {
        return ID;
    }

    int getLoadTime()
    {
        return LoadTime;
    }

    int getDistance()
    {
        return CargoDistance;
    }

    //For AutoP
    int GetWaitTimeDays(Time CurrentTime)
    {
        int diff = Time::dayDiff(CurrentTime,PreparationTime);
        return diff;

    }

    //For MaxW
    int GetWaitTimeHours(Time CurrentTime)
    {
        int diff = Time::hourDiff(CurrentTime,PreparationTime);
        return diff;
    }

    //For output file (phase 2)
    void SetWaitTime(Time CurrentTime)
    {
        Time WT = CurrentTime.Timediff(CurrentTime, PreparationTime);
        WaitTime = WT;

    }
  

};