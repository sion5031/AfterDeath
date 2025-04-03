#include "Item.h"

Item::Item()
{
}

void Item::SetEquipedTrue()
{
	Equiped = true;
}

void Item::SetEquipedFalse()
{
	Equiped = false;
}

void Item::SetName(string name)
{
	Name = name;
}

void Item::SetSN(int SN)
{
	this->SN = SN;
}

void Item::SetAtkPoint(int atkPoint)
{
	AtkPoint = atkPoint;
}

void Item::SetDefPoint(int defPoint)
{
	DefPoint = defPoint;
}

void Item::SetEffectPoint(int effectPoint)
{
	EffectPoint = effectPoint;
}

void Item::SetEquiped(bool equiped)
{
	Equiped = equiped;
}

string Item::GetName()
{
	return Name;
}

int Item::GetSN()
{
	return this->SN;
}

int Item::GetAtkPoint()
{
	return AtkPoint;
}

int Item::GetDefPoint()
{
	return DefPoint;
}

int Item::GetEffectPoint()
{
	return EffectPoint;
}

bool Item::GetEquiped()
{
	return Equiped;
}
