#include "Inventory.h"

Item* Inventory::FindItem(int num)
{
	return Items->at(num);
}

void Inventory::ArrangeInventory()
{
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
	for (int i = 0;i <= Items->size();i++) {
		if (Items->find(i) == Items->end()) {
			Items->insert({ i, item });
			break;
		}
	}
	cout << item->GetName() << "을 획득했습니다." << endl;
}

void Inventory::RemoveItem(int num)
{
	if (bCheckPresence(num))
	{
		Items->erase(num);//맞나?
	}
}

void Inventory::TryUse(int num, shared_ptr<Creature> player)
{
	if (bCheckPresence(num))
	{
		IConsumable* consumable = dynamic_cast<IConsumable*>(FindItem(num));
		if (consumable) {
			consumable->UseItem(player);
		}
		else {
			std::cout << "이 아이템은 사용할 수 없습니다.\n";
		}
	}
}

void Inventory::TryEquip(int num)
{
	if (bCheckPresence(num))
	{
		IEquipable* equipable = dynamic_cast<IEquipable*>(FindItem(num));
		if (equipable) {
			equipable->EquipItem();
		}
		else {
			std::cout << "이 아이템은 장비할 수 없습니다.\n";
		}
	}
}

void Inventory::DisplayInventory()
{
	int nonCount = 0;
	for (int i = 0;i < this->Items->size() + nonCount;i++) {
		if (bCheckPresence(i))
		{
			cout << '#' << i + 1 << '\t' << this->Items->at(i)->GetName() << endl;
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

int Inventory::GetTotalEquipmentAtk()
{
	int nonCount = 0;
	int sum = 0;
	for (int i = 0;i < Items->size() + nonCount;i++)
	{
		if (bCheckPresence(i))
		{
			IEquipable* equipable = dynamic_cast<IEquipable*>(FindItem(i));
			if (equipable)
			{
				sum += equipable->GetEquipAtkPoint();
			}
		}
		else
		{
			nonCount++;
		}
	}
	return sum;
}

int Inventory::GetTotalEquipmentDef()
{
	int nonCount = 0;
	int sum = 0;
	for (int i = 0;i < Items->size() + nonCount;i++)
	{
		if (bCheckPresence(i))
		{
			IEquipable* equipable = dynamic_cast<IEquipable*>(FindItem(i));
			if (equipable)
			{
				sum += equipable->GetEquipDefPoint();
			}
		}
		else
		{
			nonCount++;
		}
	}
	return sum;
}

int Inventory::GetTotalEquipmentMaxHp()
{
	int nonCount = 0;
	int sum = 0;
	for (int i = 0;i < Items->size() + nonCount;i++)
	{
		if (bCheckPresence(i))
		{
			IEquipable* equipable = dynamic_cast<IEquipable*>(FindItem(i));
			if (equipable)
			{
				sum += equipable->GetEquipHpPoint();
			}
		}
		else
		{
			nonCount++;
		}
	}
	return sum;
}

int Inventory::GetTotalEquipmentMaxMp()
{
	int nonCount = 0;
	int sum = 0;
	for (int i = 0;i < Items->size() + nonCount;i++)
	{
		if (bCheckPresence(i))
		{
			IEquipable* equipable = dynamic_cast<IEquipable*>(FindItem(i));
			if (equipable)
			{
				sum += equipable->GetEquipMpPoint();
			}
		}
		else
		{
			nonCount++;
		}
	}
	return sum;
}
