#pragma once

class Item;
class Skill;

class IPlayable
{
public:
	virtual ~IPlayable() = default;

	virtual void DisplayInventory() = 0;
	virtual void AddInventory(Item* item) = 0;
	virtual void SelectInventoryItem(int num) = 0;
	virtual void AddSkill(Skill* skill) = 0;
	virtual void PlusDeathCount() = 0;
};