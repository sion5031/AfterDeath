#include "Player.h"
#include "LongSword.h"
#include "ShortSword.h"
#include "Upper.h"
#include "Lower.h"
#include "Glove.h"
#include "Shoes.h"
#include "Shield.h"
#include "HpPotion.h"
#include "MpPotion.h"

void Player::UseItem(int num, shared_ptr<Creature> player)
{
	MyInven->TryUse(num, player);
}

void Player::EquipItem(int num) // ���� �̿��ؼ� ���ϰ� ����??
{
	if (MyInven->GetSN(num) == 100) // ���
	{
		if (Equipments->myShield == nullptr)
		{
			if (Equipments->myWeapon != nullptr)
			{
				Equipments->myWeapon->SetEquipedFalse();
			}
			Equipments->myWeapon = MyInven->TryEquip(num);
		}
		else
		{
			cout << "����� ���п� ���� ����� �� �����ϴ�." << endl;
		}
	}
	else if (MyInven->GetSN(num) == 101) // �ܰ�
	{
		if (Equipments->myWeapon != nullptr)
		{
			Equipments->myWeapon->SetEquipedFalse();
		}
		Equipments->myWeapon = MyInven->TryEquip(num);
	}
	else if (MyInven->GetSN(num) == 110) // ����
	{
		if (Equipments->myUpper != nullptr)
		{
			Equipments->myUpper->SetEquipedFalse();
		}
		Equipments->myUpper = MyInven->TryEquip(num);
	}
	else if (MyInven->GetSN(num) == 111) // ����
	{
		if (Equipments->myLower != nullptr)
		{
			Equipments->myLower->SetEquipedFalse();
		}
		Equipments->myLower = MyInven->TryEquip(num);
	}
	else if (MyInven->GetSN(num) == 112) // �尩
	{
		if (Equipments->myGlove != nullptr)
		{
			Equipments->myGlove->SetEquipedFalse();
		}
		Equipments->myGlove = MyInven->TryEquip(num);
	}
	else if (MyInven->GetSN(num) == 113) // �Ź�
	{
		if (Equipments->myShoes != nullptr)
		{
			Equipments->myShoes->SetEquipedFalse();
		}
		Equipments->myShoes = MyInven->TryEquip(num);
	}
	else if (MyInven->GetSN(num) == 114) // ����
	{
		if (Equipments->myWeapon != nullptr && Equipments->myWeapon->GetSN() == 101)
		{
			if (Equipments->myShield != nullptr)
			{
				Equipments->myShield->SetEquipedFalse();
			}
			Equipments->myShield = MyInven->TryEquip(num);
		}
		else
		{
			cout << "���д� �ܰ˰��� ���� ����� �� �����ϴ�." << endl;
		}
	}
}

void Player::ShowTotalStatus()
{
}

Player::Player()
{
	Name = "ȫ�浿";
	Type = 0;
	MaxHp = 100;
	Hp = MaxHp;
	MaxMp = 50;
	Mp = MaxMp;
	Attack = 10;
	Defense = 5;
	Skills = new vector<Skill*>;
	//Equipments = new EquipedE; //Creature �����ڿ��� ����
	DeathCount = 0;
	MyInven = new Inventory();

	cout << "ĳ���͸� �����߽��ϴ�." << endl;
}

Player::Player(string name)
{
	Name = name;
	Type = 0;
	MaxHp = 50;
	Hp = MaxHp;
	MaxMp = 50;
	Mp = MaxMp;
	Attack = 35;
	Defense = 3;
	Skills = new vector<Skill*>;

	DeathCount = 0;
	MyInven = new Inventory();


	MyInven->AddItem(new LongSword());
	//MyInven->TryEquip(0);
	EquipItem(0); // ������ �κ����� ã�Ƽ� �� ��ȣ �־��
	MyInven->AddItem(new HpPotion(5));


	cout << "ĳ���͸� �����߽��ϴ�." << endl;
}

Player::~Player()
{
}

void Player::DisplayInventory()
{
	this->MyInven->DisplayInventory();
}

void Player::AddInventory(Item*)
{
}

void Player::SelectInventoryItem(int num)
{
	if (MyInven->bCheckPresence(num))
	{
		char usage;

		cout << "1. ����ϱ�" << endl << endl << "2. ����ϱ�" << endl << endl << "3. �����ϱ�" << endl;
		cout << "===============================================" << endl << endl;
		cout << "�ൿ�� �������ּ���: ";
		usage = _getche();

		if (usage == '1')
		{
			this->MyInven->TryUse(num, GetShared()); // �̰� �³�????
		}
		else if (usage == '2')
		{
			this->MyInven->TryEquip(num);
		}
		else if (usage == '3')
		{
			this->MyInven->RemoveItem(num);
		}
		else
		{
			cout << "�߸��� �����Դϴ�." << endl << "�ൿ�� ��ŵ�մϴ�." << endl;
		}
	}
	else
	{
		cout << "�߸��� �����Դϴ�." << endl << "�ൿ�� ��ŵ�մϴ�." << endl;
	}
}

vector<Item*>* Player::GetAllInventoryItems()
{
	return MyInven->GetAllInventoryItems();
}

void Player::InitInventory()
{
	MyInven->InitInventory();
}

void Player::AddSkill(Skill* skill)
{
	Skills->push_back(skill);
}

void Player::PlusDeathCount()
{
	DeathCount++;
}

void Player::UseSkill(shared_ptr<Creature> creature)
{
}

void Player::Die()
{
}

void Player::SetDeathCount(int deathCount)
{
	DeathCount = deathCount;
}

int Player::GetDeathCount()
{
	return DeathCount;
}

//int Player::GetTotalAtk()
//{
//	return MyInven->GetTotalEquipmentAtk() + Attack;
//}
//
//int Player::GetTotalDef()
//{
//	return MyInven->GetTotalEquipmentDef() + Defense;
//}
//
//int Player::GetTotalMaxHp()
//{
//	return MyInven->GetTotalEquipmentMaxHp() + MaxHp;
//}
//
//int Player::GetTotalMaxMp()
//{
//	return MyInven->GetTotalEquipmentMaxMp() + MaxMp;
//}
