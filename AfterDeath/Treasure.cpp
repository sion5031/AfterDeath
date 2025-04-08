#include "Treasure.h"

Treasure::Treasure()
{
	Items = new vector<Item*>;
	//Items = nullptr;
	NewSkill = nullptr;
}

Treasure::~Treasure()
{
}

void Treasure::SetItems(vector<Item*>* treasure)
{
	this->Items = treasure;
}

void Treasure::AddItems(Item* item)
{
	this->Items->push_back(item);
}

void Treasure::SetNewSkill(Skill* skill)
{
	this->NewSkill = skill;
}

vector<Item*>* Treasure::GetItems()
{
	return Items;
}

Skill* Treasure::GetNewSkill()
{
	return NewSkill;
}
