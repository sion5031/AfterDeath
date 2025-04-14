#include <string>
#include "Skill.h"

Skill::Skill()
{
}

void Skill::PlusLevel(int level)
{
	Level += level;
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

string Skill::GetEnhancedName()
{
	return Name + " +" + to_string(Level);
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

int Skill::GetMpConsume()
{
	return MpConsume;
}
