#pragma once
#include "Item.h"
#include "IConsumable.h"

class Consumable : public Item, public IConsumable
{
private:


public:
	virtual ~Consumable(){}

	virtual void UseItem(shared_ptr<Creature> player) = 0;
};