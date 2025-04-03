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
	cout << item->GetName() << "�� ȹ���߽��ϴ�." << endl;
}

void Inventory::RemoveItem(int num)
{
	if (bCheckPresence(num))
	{
		Items->erase(num);//�³�?
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
			std::cout << "�� �������� ����� �� �����ϴ�.\n";
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
			std::cout << "�� �������� ����� �� �����ϴ�.\n";
		}
	}
}

void Inventory::DisplayInventory()
{
	for (int i = 0;i < this->Items->size();i++) {
		cout << '#' << i+1 << '\t' << this->Items->at(i)->GetName() << endl;
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
