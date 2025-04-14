#pragma once
//#include "Creature.h"

class Creature;

class IEquipable
{
public:
	virtual ~IEquipable() = default;

	virtual void EquipItem() = 0;

	virtual int GetEquipAtkPoint() = 0;
	virtual int GetEquipDefPoint() = 0;
	virtual int GetEquipHpPoint() = 0;
	virtual int GetEquipMpPoint() = 0;
};