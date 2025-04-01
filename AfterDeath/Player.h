#pragma once

#include "Creature.h"
#include "Inventory.h"

class Player : public Creature
{
private:
	int DeathCount;

	void UseItem(int num);
	void EquipItem(int num);
	void ShowTotalStatus();

public:
	Player();
	~Player();

	void DisplayInventory();
	void AddInventory(Item*);
	void SelectInventoryItem(int num);
	void PlusDeathCount(int num);
	void UseSkill() override;
	void Die() override;

	void SetDeathCount(int deathCount);
	int GetDeathCount();
};