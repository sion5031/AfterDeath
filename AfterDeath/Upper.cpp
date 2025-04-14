#include "Upper.h"

Upper::Upper()
{
	this->SetSN(110);
	this->SetName("상의");
	this->SetDefPoint(10);
}

Upper::Upper(int level)
{
	this->SetSN(110);
	this->SetName("상의 +" + to_string(level));
	this->SetDefPoint(10 * (1 + 0.5 * level));
}

Upper::~Upper()
{
}

