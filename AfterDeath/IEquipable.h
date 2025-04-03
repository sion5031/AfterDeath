#pragma once
//#include "Creature.h"

class Creature;

class IEquipable
{
public:
	virtual ~IEquipable() = default;

	virtual void EquipItem() = 0;
};