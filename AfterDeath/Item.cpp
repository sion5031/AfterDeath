#include "Item.h"

Item::Item()
{
	AtkPoint = 0;
	DefPoint = 0;
	EffectPoint = 0;
	Equiped = false;
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

void Item::SetHpPoint(int hpPoint)
{
	HpPoint = hpPoint;
}

void Item::SetMpPoint(int mpPoint)
{
	MpPoint = mpPoint;
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

int Item::GetHpPoint()
{
	return HpPoint;
}

int Item::GetMpPoint()
{
	return MpPoint;
}

int Item::GetEffectPoint()
{
	return EffectPoint;
}

bool Item::GetEquiped()
{
	return Equiped;
}
