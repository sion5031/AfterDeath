#include "ShortSword.h"

ShortSword::ShortSword()
{
	this->SetSN(101);
	this->SetName("단검");
	this->SetAtkPoint(8);
}

ShortSword::ShortSword(int level)
{
	this->SetSN(101);
	this->SetName("단검 +" + to_string(level));
	this->SetAtkPoint(8 * (1 + 0.5 * level));
}

ShortSword::~ShortSword()
{
}
