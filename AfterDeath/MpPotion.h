#pragma once
#include "Consumable.h"

class MpPotion : public Consumable
{
private:


public:
	MpPotion(int num);
	//virtual ~MpPotion(){ cout << "~MpPotion()" << endl; }
	~MpPotion();

	void UseItem(shared_ptr<Creature> player) override;
};