#pragma once

#include "Creature.h"
#include "Inventory.h"
#include "IPlayable.h"

class Player : public Creature, public IPlayable
{
private:
	int DeathCount;
	Inventory* MyInven;

	void UseItem(int num);
	void EquipItem(int num);
	void ShowTotalStatus();

public:
	Player();
	Player(string name);
	~Player();

	void DisplayInventory() override;
	void AddInventory(Item* item) override;
	void SelectInventoryItem(int num) override;
	void AddSkill(Skill* skill) override;
	void PlusDeathCount(int num) override;

	void UseSkill() override;
	void Die() override;

	void SetDeathCount(int deathCount);
	int GetDeathCount();
};