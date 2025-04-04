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

void Player::EquipItem(int num) // 패턴 이용해서 편하게 가능??
{
	if (MyInven->GetSN(num) == 100) // 장검
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
			cout << "장검은 방패와 같이 사용할 수 없습니다." << endl;
		}
	}
	else if (MyInven->GetSN(num) == 101) // 단검
	{
		if (Equipments->myWeapon != nullptr)
		{
			Equipments->myWeapon->SetEquipedFalse();
		}
		Equipments->myWeapon = MyInven->TryEquip(num);
	}
	else if (MyInven->GetSN(num) == 110) // 상의
	{
		if (Equipments->myUpper != nullptr)
		{
			Equipments->myUpper->SetEquipedFalse();
		}
		Equipments->myUpper = MyInven->TryEquip(num);
	}
	else if (MyInven->GetSN(num) == 111) // 하의
	{
		if (Equipments->myLower != nullptr)
		{
			Equipments->myLower->SetEquipedFalse();
		}
		Equipments->myLower = MyInven->TryEquip(num);
	}
	else if (MyInven->GetSN(num) == 112) // 장갑
	{
		if (Equipments->myGlove != nullptr)
		{
			Equipments->myGlove->SetEquipedFalse();
		}
		Equipments->myGlove = MyInven->TryEquip(num);
	}
	else if (MyInven->GetSN(num) == 113) // 신발
	{
		if (Equipments->myShoes != nullptr)
		{
			Equipments->myShoes->SetEquipedFalse();
		}
		Equipments->myShoes = MyInven->TryEquip(num);
	}
	else if (MyInven->GetSN(num) == 114) // 방패
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
			cout << "방패는 단검과만 같이 사용할 수 없습니다." << endl;
		}
	}
}

void Player::ShowTotalStatus()
{
}

Player::Player()
{
	Name = "홍길동";
	Type = 0;
	MaxHp = 100;
	Hp = MaxHp;
	MaxMp = 50;
	Mp = MaxMp;
	Attack = 10;
	Defense = 5;
	Skills = new vector<Skill*>;
	//Equipments = new EquipedE; //Creature 생성자에서 생성
	DeathCount = 0;
	MyInven = new Inventory();

	cout << "캐릭터를 생성했습니다." << endl;
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
	EquipItem(0); // 원래는 인벤에서 찾아서 그 번호 넣어야
	MyInven->AddItem(new HpPotion(5));


	cout << "캐릭터를 생성했습니다." << endl;
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

		cout << "1. 사용하기" << endl << endl << "2. 장비하기" << endl << endl << "3. 제거하기" << endl;
		cout << "===============================================" << endl << endl;
		cout << "행동을 선택해주세요: ";
		usage = _getche();

		if (usage == '1')
		{
			this->MyInven->TryUse(num, GetShared()); // 이게 맞나????
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
			cout << "잘못된 선택입니다." << endl << "행동을 스킵합니다." << endl;
		}
	}
	else
	{
		cout << "잘못된 선택입니다." << endl << "행동을 스킵합니다." << endl;
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
