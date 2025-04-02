#include "Creature.h"

void Creature::Fight(Creature* player, Creature* monster)
{

}

void Creature::NormalAttack(Creature*)
{
}

void Creature::CalcHp(int hp)
{
	Hp += hp;
}

void Creature::CalcMp(int mp)
{
	Mp += mp;
}

void Creature::SetName(string Name)
{
	this->Name = Name;
}

void Creature::SetType(int Type)
{
	this->Type = Type;
}

void Creature::SetMaxHp(int MaxHp)
{
	this->MaxHp = MaxHp;
}

void Creature::SetHp(int Hp)
{
	this->Hp = Hp;
}

void Creature::SetMaxMp(int MaxMp)
{
	this->MaxMp = MaxMp;
}

void Creature::SetMp(int Mp)
{
	this->Mp = Mp;
}

void Creature::SetAtk(int Atk)
{
	this->Attack = Atk;
}

void Creature::SetDef(int Def)
{
	this->Defense = Def;
}

string Creature::GetName()
{
	return Name;
}

int Creature::GetType()
{
	return Type;
}

int Creature::GetMaxHp()
{
	return MaxHp;
}

int Creature::GetHp()
{
	return Hp;
}

int Creature::GetMaxMp()
{
	return MaxMp;
}

int Creature::GetMp()
{
	return Mp;
}

int Creature::GetAttack()
{
	return Attack;
}

int Creature::GetDefense()
{
	return Defense;
}
