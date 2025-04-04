#pragma once
//#include "Creature.h"

class Creature;

class IConsumable
{
public:
	virtual ~IConsumable() = default;

	virtual void UseItem(shared_ptr<Creature> player) = 0;
	virtual void SetNumber(int num) = 0;
	virtual int GetNumber() = 0;
	virtual void PlusNumber(int num) = 0;
};