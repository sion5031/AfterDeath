#include "Shoes.h"

Shoes::Shoes()
{
	this->SetSN(113);
	this->SetName("신발");
	this->SetDefPoint(6);
	this->SetHpPoint(20);
}

Shoes::Shoes(int level)
{
	this->SetSN(113);
	this->SetName("신발 +" + to_string(level));
	this->SetDefPoint(6 * (1 + 0.5 * level));
	this->SetHpPoint(20 * (1 + 0.5 * level));
}

Shoes::~Shoes()
{
}

