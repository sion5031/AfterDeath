#include "Lower.h"

Lower::Lower()
{
	this->SetSN(111);
	this->SetName("하의");
	this->SetDefPoint(8);
}

Lower::Lower(int level)
{
	this->SetSN(111);
	this->SetName("하의 +" + to_string(level));
	this->SetDefPoint(8 * (1 + 0.5 * level));
}

Lower::~Lower()
{
}

