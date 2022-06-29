#pragma once
#include "Events.h"
class CancellationEvent :
    public Events
{
public:
    CancellationEvent();
    void execute(Company* company);
    ~CancellationEvent();
    void LoadEvent(ifstream& inputFile);
};

