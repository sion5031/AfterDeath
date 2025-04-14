#pragma once
#include "Consumable.h"

class HpPotion : public Consumable
{
private:


public:
	HpPotion(int num);
	//virtual ~HpPotion(){ cout << "~HpPotion()" << endl; }
	~HpPotion();

	string UseItem(shared_ptr<Creature> player) override;
};