#pragma once
#include <iostream>
#include <map>

#include "Item.h"

using namespace std;

class Inventory
{
private:
	map<int, Item*>* Items;

	void ArrangeInventory();
	void FindItem();

public:
	Inventory();
	~Inventory();

	void AddItem(Item* item);
	void RemoveItem(int num);
	void TryUse(int num);
	void TryEquip(int num);
	void DisplayInventory();

};