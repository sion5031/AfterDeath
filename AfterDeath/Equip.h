#pragma once
#include "Item.h"
#include "IEquipable.h"

class Equip : public Item, public IEquipable
{
private:


public:
	Equip(){}
	//virtual ~Equip(){ cout << "~Equip()" << endl; }
	virtual ~Equip(){}

	void EquipItem() override;
};