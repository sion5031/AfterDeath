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
	bool bCompareByValue(const pair<int, Item*>& a, const pair<int, Item*>& b);

public:
	Inventory();
	~Inventory();

	void AddItem(Item* item);
	void RemoveItem(int num);
	Item* TryUse(int num);
	Item* TryEquip(int num);
	void DisplayInventory();
	vector<Item*>* GetAllInventoryItems();
	void InitInventory();
	void ArrangeInventory();
	bool bCheckPresence(int num);

	int GetSN(int num);

	//int GetTotalEquipmentAtk();
	//int GetTotalEquipmentDef();
	//int GetTotalEquipmentMaxHp();
	//int GetTotalEquipmentMaxMp();
};