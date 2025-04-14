#include "Shield.h"

Shield::Shield()
{	
	this->SetSN(114);
	this->SetName("방패");
	this->SetDefPoint(6);
}

Shield::Shield(int level)
{
	this->SetSN(114);
	this->SetName("방패 +" + to_string(level));
	this->SetDefPoint(6 * (1 + 0.5 * level));
}

Shield::~Shield()
{
}

