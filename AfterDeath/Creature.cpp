#include "Creature.h"

Creature::Creature()
{
}

Creature::~Creature()
{
}



void Creature::SetCName(string CName)
{
	this->CName = CName;
}

void Creature::SetCType(int CType)
{
	this->CType = CType;
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
	this->Atk = Atk;
}

void Creature::SetDef(int Def)
{
	this->Def = Def;
}

string Creature::GetCName()
{
	return CName;
}

int Creature::GetCType()
{
	return CType;
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

int Creature::GetAtk()
{
	return Atk;
}

int Creature::GetDef()
{
	return Def;
}
