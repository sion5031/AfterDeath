#pragma once
#include "Item.h"
#include "IConsumable.h"

class Consumable : public Item, public IConsumable
{
private:

protected:
	int Number;

public:
	Consumable(){}
	Consumable(int num);
	virtual ~Consumable(){}

	virtual void UseItem(shared_ptr<Creature> player) = 0;

	void SetNumber(int num) override;
	int GetNumber() override;
	void PlusNumber(int num) override;
};