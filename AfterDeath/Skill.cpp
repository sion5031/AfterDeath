#include "Skill.h"

Skill::Skill()
{
}

void Skill::SetName(string name)
{
	Name = name;
}

void Skill::SetType(int type)
{
	Type = type;
}

void Skill::SetLevel(int level)
{
	Level = level;
}

void Skill::SetEffectValue(int value)
{
	EffectValue = value;
}

string Skill::GetName()
{
	return Name;
}

int Skill::GetType()
{
	return Type;
}

int Skill::GetLevel()
{
	return Level;
}

int Skill::GetEffectValue()
{
	return EffectValue;
}
