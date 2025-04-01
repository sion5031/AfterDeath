#include "Creature.h"

void Creature::Fight(Creature* player, Creature* monster)
{
}

void Creature::NormalAttack(Creature*)
{
}

void Creature::HitBy(int damage)
{
}

void Creature::CalcHp(int hp)
{
}

void Creature::CalcMp(int mp)
{
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

string Creature::GetCName()
{
	return Name;
}

int Creature::GetCType()
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
