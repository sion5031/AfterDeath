#include <algorithm>

#include "Inventory.h"

Item* Inventory::FindItem(int num)
{
	return Items->at(num);
}

void Inventory::ArrangeInventory()
{
	int itemsSize = Items->size();
	vector<pair<int, Item*>> ItemsVector(Items->begin(), Items->end());
	//sort(ItemsVector.begin(), ItemsVector.end(), bCompareByValue);
	sort(ItemsVector.begin(), ItemsVector.end(), // 이해하기...
		[](const pair<int, Item*>& a, const pair<int, Item*>& b) {
			return a.second->GetSN() < b.second->GetSN();
		});
	Items->clear();

	for (const auto& pair : ItemsVector)
	{
		(*Items)[pair.first] = pair.second;
	}
}

bool Inventory::bCompareByValue(const pair<int, Item*>& a, const pair<int, Item*>& b) // pair 이해 못함
{
	return a.second->GetSN() < b.second->GetSN();
}

Inventory::Inventory()
{
	Items = new map<int, Item*>;
}

Inventory::~Inventory()
{
}

void Inventory::AddItem(Item* item)
{
	IConsumable* consumableItem1 = dynamic_cast<IConsumable*>(item);
	if (consumableItem1)
	{
		cout << item->GetName() << "(" << consumableItem1->GetNumber() << ")" << "을 획득했습니다." << endl;
	}
	else
	{
		cout << item->GetName() << "을 획득했습니다." << endl;
	}

	int nonCount = 0;
	int size = Items->size();
	for (int i = 0;i <= size + nonCount;i++) {
		if (Items->find(i) != Items->end() && Items->at(i)->GetSN() < 100 && Items->at(i)->GetSN() == item->GetSN())
		{
			IConsumable* consumableItem2 = dynamic_cast<IConsumable*>(Items->at(i));
			consumableItem2->PlusNumber(consumableItem1->GetNumber());

			return;
		}
	}

	nonCount = 0;
	for (int i = 0;i <= size + nonCount;i++) {
		if (Items->find(i) == Items->end()) {
			Items->insert({ i, item });
			break;
		}
	}	
}

void Inventory::RemoveItem(int num)
{
	if (bCheckPresence(num))
	{
		Items->erase(num);//맞나?
	}
}

Item* Inventory::TryUse(int num)
{
	if (bCheckPresence(num))
	{
		IConsumable* consumable = dynamic_cast<IConsumable*>(FindItem(num));
		if (consumable) {
			//consumable->UseItem(player); // 안 쓰고 넘길게.
			return FindItem(num);
		}
		else {
			std::cout << "이 아이템은 사용할 수 없습니다.\n";
		}
	}
	return nullptr;
}

Item* Inventory::TryEquip(int num)
{
	if (bCheckPresence(num))
	{
		IEquipable* equipable = dynamic_cast<IEquipable*>(FindItem(num));
		if (equipable) {
			equipable->EquipItem();
			return FindItem(num);
		}
		else {
			std::cout << "이 아이템은 장비할 수 없습니다.\n";
			return nullptr;
		}
	}
	return nullptr;
}

void Inventory::DisplayInventory()
{
	int nonCount = 0;
	cout << endl;
	for (int i = 0;i < this->Items->size() + nonCount;i++) {
		if (bCheckPresence(i))
		{
			if (this->Items->at(i)->GetSN() >= 100)
			{
				if (this->Items->at(i)->GetEquiped() == true)
				{
					cout << '#' << i + 1 << '\t' << this->Items->at(i)->GetName() << "\t\t" << "장착" << endl;
				}
				else
				{
					cout << '#' << i + 1 << '\t' << this->Items->at(i)->GetName() << endl;
				}
			}
			else
			{
				IConsumable* consumableItem = dynamic_cast<IConsumable*>(this->Items->at(i));
				cout << '#' << i + 1 << '\t' << this->Items->at(i)->GetName() << "\t\t" << consumableItem->GetNumber() << endl;
			}
		}
		else
		{
			nonCount++;
		}
	}
}

vector<Item*>* Inventory::GetAllInventoryItems()
{
	int nonCount = 0;
	vector<Item*>* allItems = new vector<Item*>;
	for (int i = 0;i < Items->size() + nonCount;i++)
	{
		if (bCheckPresence(i))
		{
			//if (FindItem(i)->GetEquiped() == true) // 죽었는지 모름
			//{
			//	FindItem(i)->SetEquipedFalse();
			//}
			allItems->push_back(FindItem(i));
		}
		else
		{
			nonCount++;
		}
	}
	if (allItems->size() == 0)
	{
		return nullptr;
	}
	else
	{
		return allItems;
	}
}

void Inventory::InitInventory()
{
	int nonCount = 0;
	int itemsSize = Items->size();
	for (int i = 0;i < itemsSize + nonCount;i++)
	{
		if (bCheckPresence(i))
		{
			if (FindItem(i)->GetEquiped() == true)
			{
				FindItem(i)->SetEquipedFalse();
			}
			RemoveItem(i);
		}
		else
		{
			nonCount++;
		}
	}
}

bool Inventory::bCheckPresence(int num)
{
	if (Items->find(num) == Items->end())
	{
		return false;
	}
	return true;
}

int Inventory::GetSN(int num)
{
	return FindItem(num)->GetSN();
}

//int Inventory::GetTotalEquipmentAtk()
//{
//	int nonCount = 0;
//	int sum = 0;
//	for (int i = 0;i < Items->size() + nonCount;i++)
//	{
//		if (bCheckPresence(i))
//		{
//			if (FindItem(i)->GetEquiped() == true)
//			{
//				IEquipable* equipable = dynamic_cast<IEquipable*>(FindItem(i));
//				if (equipable)
//				{
//					sum += equipable->GetEquipAtkPoint();
//				}
//			}
//		}
//		else
//		{
//			nonCount++;
//		}
//	}
//	return sum;
//}
//
//int Inventory::GetTotalEquipmentDef()
//{
//	int nonCount = 0;
//	int sum = 0;
//	for (int i = 0;i < Items->size() + nonCount;i++)
//	{
//		if (bCheckPresence(i))
//		{
//			if (FindItem(i)->GetEquiped() == true)
//			{
//				IEquipable* equipable = dynamic_cast<IEquipable*>(FindItem(i));
//				if (equipable)
//				{
//					sum += equipable->GetEquipDefPoint();
//				}
//			}
//		}
//		else
//		{
//			nonCount++;
//		}
//	}
//	return sum;
//}
//
//int Inventory::GetTotalEquipmentMaxHp()
//{
//	int nonCount = 0;
//	int sum = 0;
//	for (int i = 0;i < Items->size() + nonCount;i++)
//	{
//		if (bCheckPresence(i))
//		{
//			if (FindItem(i)->GetEquiped() == true)
//			{
//				IEquipable* equipable = dynamic_cast<IEquipable*>(FindItem(i));
//				if (equipable)
//				{
//					sum += equipable->GetEquipHpPoint();
//				}
//			}
//		}
//		else
//		{
//			nonCount++;
//		}
//	}
//	return sum;
//}
//
//int Inventory::GetTotalEquipmentMaxMp()
//{
//	int nonCount = 0;
//	int sum = 0;
//	for (int i = 0;i < Items->size() + nonCount;i++)
//	{
//		if (bCheckPresence(i))
//		{
//			if (FindItem(i)->GetEquiped() == true)
//			{
//				IEquipable* equipable = dynamic_cast<IEquipable*>(FindItem(i));
//				if (equipable)
//				{
//					sum += equipable->GetEquipMpPoint();
//				}
//			}
//		}
//		else
//		{
//			nonCount++;
//		}
//	}
//	return sum;
//}
