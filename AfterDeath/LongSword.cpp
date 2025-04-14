#include "LongSword.h"

LongSword::LongSword()
{
	this->SetSN(100);
	this->SetName("장검");
	this->SetAtkPoint(10);
}

LongSword::LongSword(int level)
{
	this->SetSN(100);
	this->SetName("장검 +" + to_string(level));
	this->SetAtkPoint(10*(1+0.5*level));
}

LongSword::~LongSword()
{
}

