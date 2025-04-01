#pragma once
#include "Item.h"
#include "IConsumable.h"

class Consumable : public Item, public IConsumable
{
private:


public:
	virtual ~Consumable(){}

	void UseItem() override;
};