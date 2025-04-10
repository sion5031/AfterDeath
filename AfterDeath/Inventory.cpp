#include <algorithm>

#include "Inventory.h"
#include "ConsoleGotoxy.h"

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

	int newKey = 0;
	for (const auto& pair : ItemsVector)
	{
		(*Items)[newKey++] = pair.second;
	}
}

void Inventory::CheckZeroInventory()
{
	int nonCount = 0;
	int size = Items->size();
	for (int i = 0;i < size + nonCount;i++) {
		if (Items->find(i) != Items->end()) {
			IConsumable* consumableItem = dynamic_cast<IConsumable*>(Items->at(i));
			if (consumableItem)
			{
				consumableItem->GetNumber() <= 0;
				//delete
				Items->erase(i);
			}
		}
		else
		{
			nonCount++;
		}
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

string Inventory::AddItem(Item* item)
{
	string message;
	IConsumable* consumableItem1 = dynamic_cast<IConsumable*>(item);
	if (consumableItem1)
	{
		message = item->GetName() + "(" + to_string(consumableItem1->GetNumber()) + ") 을 획득했습니다.";
	}
	else
	{
		message = item->GetName() + "을 획득했습니다.";
	}

	int nonCount = 0;
	int size = Items->size();
	for (int i = 0;i <= size + nonCount;i++) {
		if (Items->find(i) != Items->end())
		{
			if (Items->at(i)->GetSN() < 100 && Items->at(i)->GetSN() == item->GetSN())
			{
				IConsumable* consumableItem2 = dynamic_cast<IConsumable*>(Items->at(i));
				consumableItem2->PlusNumber(consumableItem1->GetNumber());

				return message;
			}
		}
		else
		{
			if (i != size + nonCount - 1)
			{
				break;
			}
			nonCount++;
		}
	}

	nonCount = 0;
	for (int i = 0;i <= size + nonCount;i++) {
		if (Items->find(i) == Items->end()) {
			Items->insert({ i, item });
			break;
		}
		else
		{
			nonCount++;
		}
	}
	return message;
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
			return nullptr;
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
			return nullptr;
		}
	}
	return nullptr;
}

void Inventory::DisplayInventory()
{
	ArrangeInventory();

	int nonCount = 0;
	int printCount = 0;

	GotoxyPreparePrintMenu(-2);
	cout << "<인벤토리>";

	for (int i = 0;i < this->Items->size() + nonCount;i++) {
		if (bCheckPresence(i))
		{
			GotoxyPreparePrintMenu(printCount);
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
			printCount++;
		}
		else
		{
			nonCount++;
		}
	}
}

void Inventory::DisplayInventoryDetail()
{
	ArrangeInventory();

	int nonCount = 0;
	int printCount = 0;

	GotoxyPreparePrintMenu(-2);
	cout << "<인벤토리>";

	for (int i = 0;i < this->Items->size() + nonCount;i++) {
		if (bCheckPresence(i))
		{
			GotoxyPreparePrintMenu(printCount);
			if (this->Items->at(i)->GetSN() >= 100)
			{
				if (this->Items->at(i)->GetEquiped() == true)
				{
					cout << '#' << i + 1 << '\t' << this->Items->at(i)->GetName() << "\t\t" << "장착\t";
				}
				else
				{
					cout << '#' << i + 1 << '\t' << this->Items->at(i)->GetName() << "\t\t\t";
				}
				if (this->Items->at(i)->GetAtkPoint() > 0)
				{
					cout << "Atk(" << this->Items->at(i)->GetAtkPoint() << ")\t";
				}
				if (this->Items->at(i)->GetDefPoint() > 0)
				{
					cout << "Def(" << this->Items->at(i)->GetDefPoint() << ")\t";
				}
				if (this->Items->at(i)->GetHpPoint() > 0)
				{
					cout << "MaxHP(" << this->Items->at(i)->GetHpPoint() << ")\t";
				}
				if (this->Items->at(i)->GetMpPoint() > 0)
				{
					cout << "MaxMP(" << this->Items->at(i)->GetMpPoint() << ")\t";
				}
			}
			else
			{
				IConsumable* consumableItem = dynamic_cast<IConsumable*>(this->Items->at(i));
				cout << '#' << i + 1 << '\t' << this->Items->at(i)->GetName() << "\t\t" << consumableItem->GetNumber();
			}
			printCount++;
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
