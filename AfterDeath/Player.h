#pragma once

#include "Creature.h"
#include "IPlayable.h"
#include "Inventory.h"

class Player : public Creature, public IPlayable
{
private:
	int DeathCount;
	Inventory* MyInven;


public:
	Player();
	Player(string name);
	~Player();

	void UseItem(int num, shared_ptr<Creature> player);
	void EquipItem(int num);
	void ShowTotalStatus();

	void DisplayInventory() override;
	void AddInventory(Item* item) override;
	void SelectInventoryItem(int num) override;
	vector<Item*>* GetAllInventoryItems() override;
	void InitInventory() override;
	void AddSkill(Skill* skill) override;
	void PlusDeathCount() override;

	void UseSkill(shared_ptr<Creature> creature) override;
	void Die() override;

	void SetDeathCount(int deathCount);
	int GetDeathCount();

	//int GetTotalAtk();
	//int GetTotalDef();
	//int GetTotalMaxHp();
	//int GetTotalMaxMp();
};