#include "Glove.h"

Glove::Glove()
{
	this->SetSN(112);
	this->SetName("Àå°©");
	this->SetDefPoint(3);
	this->SetMpPoint(10);
}

Glove::Glove(int level)
{
	this->SetSN(112);
	this->SetName("Àå°© +" + to_string(level));
	this->SetDefPoint(3 * (1 + 0.5 * level));
	this->SetMpPoint(10 * (1 + 0.5 * level));
}

Glove::~Glove()
{
}

