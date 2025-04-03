#pragma once
//#include "Creature.h"

class Creature;

class IConsumable
{
public:
	virtual ~IConsumable() = default;

	virtual void UseItem(shared_ptr<Creature> player) = 0;
};