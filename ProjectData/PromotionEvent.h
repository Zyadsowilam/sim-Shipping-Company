#pragma once
#include "Events.h"
class PromotionEvent :
    public Events
{
private:
    int ExtraMoney;
public:
    PromotionEvent();
    void setExtraMoney(int em);
    int getExtraMoney();
    void LoadEvent(ifstream& inputFile);
    void execute(Company* company);
    ~PromotionEvent();
};

