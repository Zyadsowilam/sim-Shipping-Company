#include "PromotionEvent.h"
#include "Company.h"
PromotionEvent::PromotionEvent()
{

}
void PromotionEvent::setExtraMoney(int em) {
	ExtraMoney = em;
}
int PromotionEvent::getExtraMoney() {
	return ExtraMoney;
}
PromotionEvent::~PromotionEvent() {

}

void PromotionEvent::execute(Company* company)
{
    company->PromoteCargo(ID, ExtraMoney);

	delete this;
	
}

void PromotionEvent::LoadEvent(ifstream& inputFile)
{
	int day, hour, ID, em;
	char buffer;
	inputFile >> day >> buffer >> hour >> ID >> em;
	Time ET(day, hour);
	setET(ET);
	setID(ID);
	setExtraMoney(em);

}