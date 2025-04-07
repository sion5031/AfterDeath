#include "Equip.h"

Equip::Equip()
{
	Equiped = false;
}

void Equip::EquipItem()
{
	cout << this->GetName() << " 을 장착했습니다.\n";
	Equiped = true;
}

int Equip::GetEquipAtkPoint()
{
	return this->AtkPoint;
}

int Equip::GetEquipDefPoint()
{
	return this->DefPoint;
}

int Equip::GetEquipHpPoint()
{
	return this->HpPoint;
}

int Equip::GetEquipMpPoint()
{
	return this->MpPoint;
}
