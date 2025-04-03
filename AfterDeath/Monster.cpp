#include "Monster.h"

Monster::Monster()
{
	Name = "°íºí¸°";
	Type = 1;
	MaxHp = 20;
	Hp = MaxHp;
	MaxMp = 5;
	Mp = MaxMp;
	Attack = 10;
	Defense = 3;
	Equipments = new vector<Item*>;	
	Skills = new vector<Skill*>;
}

Monster::~Monster()
{
}

void Monster::SetEquipments(vector<Item*>* equipments)
{
	Equipments = equipments;
}

void Monster::UseSkill(shared_ptr<Creature> creature)
{
}

void Monster::Die()
{
}

int Monster::GetTotalAtk()
{
	int sum = Attack;
	for (int i = 0;i < Equipments->size();i++)
	{
		sum += Equipments->at(i)->GetAtkPoint();
	}
	return sum;
}

int Monster::GetTotalDef()
{
	int sum = Defense;
	for (int i = 0;i < Equipments->size();i++)
	{
		sum += Equipments->at(i)->GetDefPoint();
	}
	return sum;
}

int Monster::GetTotalMaxHp()
{
	int sum = MaxHp;
	for (int i = 0;i < Equipments->size();i++)
	{
		sum += Equipments->at(i)->GetHpPoint();
	}
	return sum;
}

int Monster::GetTotalMaxMp()
{
	int sum = MaxMp;
	for (int i = 0;i < Equipments->size();i++)
	{
		sum += Equipments->at(i)->GetMpPoint();
	}
	return sum;
}
