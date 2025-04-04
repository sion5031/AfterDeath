#pragma once
#include <iostream>
#include <map>

#include "Item.h"
//#include "Creature.h"
#include "IEquipable.h"
#include "IConsumable.h"

using namespace std;

class Creature;

class Inventory
{
private:
	map<int, Item*>* Items;

	Item* FindItem(int num);
	void ArrangeInventory();

public:
	Inventory();
	~Inventory();

	void AddItem(Item* item);
	void RemoveItem(int num);
	void TryUse(int num, shared_ptr<Creature> player);
	Item* TryEquip(int num);
	void DisplayInventory();
	vector<Item*>* GetAllInventoryItems();
	void InitInventory();
	bool bCheckPresence(int num);

	int GetSN(int num);

	//int GetTotalEquipmentAtk();
	//int GetTotalEquipmentDef();
	//int GetTotalEquipmentMaxHp();
	//int GetTotalEquipmentMaxMp();
};