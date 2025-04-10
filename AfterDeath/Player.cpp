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
#include "FireBall.h"
#include "IncreaseAttack.h"
#include "AttackUp.h"
#include "DefenseUp.h"
#include "ConsoleGotoxy.h"


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
			if (Equipments->myWeapon != nullptr)
			{
				AddNotification(Equipments->myWeapon->GetName() + " 을 장착했습니다.");
			}
		}
		else
		{
			AddNotification("장검은 방패와 같이 사용할 수 없습니다.");
		}
	}
	else if (MyInven->GetSN(num) == 101) // 단검
	{
		if (Equipments->myWeapon != nullptr)
		{
			Equipments->myWeapon->SetEquipedFalse();
		}
		Equipments->myWeapon = MyInven->TryEquip(num);
		if (Equipments->myWeapon != nullptr)
		{
			AddNotification(Equipments->myWeapon->GetName() + " 을 장착했습니다.");
		}
	}
	else if (MyInven->GetSN(num) == 110) // 상의
	{
		if (Equipments->myUpper != nullptr)
		{
			Equipments->myUpper->SetEquipedFalse();
		}
		Equipments->myUpper = MyInven->TryEquip(num);
		if (Equipments->myUpper != nullptr)
		{
			AddNotification(Equipments->myUpper->GetName() + " 을 장착했습니다.");
		}
	}
	else if (MyInven->GetSN(num) == 111) // 하의
	{
		if (Equipments->myLower != nullptr)
		{
			Equipments->myLower->SetEquipedFalse();
		}
		Equipments->myLower = MyInven->TryEquip(num);
		if (Equipments->myLower != nullptr)
		{
			AddNotification(Equipments->myLower->GetName() + " 을 장착했습니다.");
		}
	}
	else if (MyInven->GetSN(num) == 112) // 장갑
	{
		if (Equipments->myGlove != nullptr)
		{
			Equipments->myGlove->SetEquipedFalse();
		}
		Equipments->myGlove = MyInven->TryEquip(num);
		if (Equipments->myGlove != nullptr)
		{
			AddNotification(Equipments->myGlove->GetName() + " 을 장착했습니다.");
		}
	}
	else if (MyInven->GetSN(num) == 113) // 신발
	{
		if (Equipments->myShoes != nullptr)
		{
			Equipments->myShoes->SetEquipedFalse();
		}
		Equipments->myShoes = MyInven->TryEquip(num);
		if (Equipments->myShoes != nullptr)
		{
			AddNotification(Equipments->myShoes->GetName() + " 을 장착했습니다.");
		}
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
			if (Equipments->myShield != nullptr)
			{
				AddNotification(Equipments->myShield->GetName() + " 을 장착했습니다.");
			}
		}
		else
		{
			AddNotification("방패는 가벼운 무기와만 같이 사용할 수 있습니다.");
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
	MaxMp = 50;
	Attack = 10;
	Defense = 5;
	Skills = new vector<Skill*>;
	//Equipments = new EquipedE; //Creature 생성자에서 생성
	DeathCount = 0;
	MyInven = new Inventory();

	Hp = GetTotalStatus()->TotalMaxHp;
	Mp = GetTotalStatus()->TotalMaxMp;

	Sleep(2000);
}

Player::Player(string name)
{
	Name = name;
	PlayerName = name;
	Type = 0;
	MaxHp = 100;
	MaxMp = 50;
	Attack = 15;
	Defense = 6;
	Skills = new vector<Skill*>;

	DeathCount = 0;
	MyInven = new Inventory();


	AddNotification(MyInven->AddItem(new LongSword()));
	//GotoxyCll(30, 0, 0);
	Gotoxy(0, 0);
	GotoxyClsLong(1);
	EquipItem(0); // 원래는 인벤에서 찾아서 그 번호 넣어야
	AddNotification(MyInven->AddItem(new HpPotion(2)));
	//GotoxyCll(30, 0, 0);
	Gotoxy(0, 0);
	GotoxyClsLong(1);


	Skill* fireBall = new FireBall();
	Skill* increaseAttack = new IncreaseAttack();
	Skill* attackUp = new AttackUp();
	Skill* defenseUp = new DefenseUp();

	Skills->push_back(fireBall);
	Skills->push_back(increaseAttack);
	Skills->push_back(attackUp);
	Skills->push_back(defenseUp);

	Hp = GetTotalStatus()->TotalMaxHp;
	Mp = GetTotalStatus()->TotalMaxMp;
}

Player::~Player()
{
}

void Player::DisplayInventory()
{
	this->MyInven->DisplayInventory();
}

void Player::DisplayInventoryDetail()
{
	this->MyInven->DisplayInventoryDetail();
}

void Player::AddInventory(Item* item)
{
	AddNotification(MyInven->AddItem(item));
}

Item* Player::SelectInventoryItem(int num)
{
	if (MyInven->bCheckPresence(num))
	{
		char usage;
		GotoxyPreparePrintMenu(0);
		cout << "1. 사용하기";
		GotoxyPreparePrintMenu(1);
		cout << "2. 장비하기";
		GotoxyPreparePrintMenu(2);
		cout << "3. 제거하기";
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		usage = _getche();
		GotoxyCll(1);

		if (usage == '1')
		{
			Item* returnItem = this->MyInven->TryUse(num);
			if (returnItem == nullptr)
			{
				AddNotification("사용할 수 없는 아이템입니다.");
			}
			return returnItem;
		}
		else if (usage == '2')
		{
			EquipItem(num);
		}
		else if (usage == '3')
		{
			this->MyInven->RemoveItem(num);
		}
		else
		{
			AddNotification("행동을 스킵합니다.");
		}
	}
	else
	{
		AddNotification("행동을 스킵합니다.");
	}
	return nullptr;
}

vector<Item*>* Player::GetAllInventoryItems()
{
	return MyInven->GetAllInventoryItems();
}

void Player::InitInventory()
{
	MyInven->InitInventory();
}

void Player::ArrangeInventory()
{
	MyInven->ArrangeInventory();
}

void Player::CheckZeroInventory()
{
	MyInven->CheckZeroInventory();
}

void Player::AddSkill(Skill* skill)
{
	for (int i = 0;i < Skills->size();i++)
	{
		if (Skills->at(i)->GetName() == skill->GetName())
		{
			Skills->at(i)->PlusLevel(skill->GetLevel());
			AddNotification(skill->GetEnhancedName() + " 을 획득해 " + Skills->at(i)->GetEnhancedName() + "으로 강화되었습니다.");
			return;
		}
	}
	Skills->push_back(skill);
	AddNotification(skill->GetEnhancedName() + " 을 획득했습니다.");
}

Skill* Player::GetSkill(int num)
{
	if (num >= 0 && num < Skills->size())
	{
		return Skills->at(num);
	}
	else
	{
		cout << "잘못된 스킬 선택" << endl;
	}
}

void Player::PlusDeathCount()
{
	DeathCount++;
}

void Player::DisplaySkills()
{
	GotoxyPreparePrintMenu(-2);
	cout << "<스킬>";
	for (int i = 0;i < Skills->size();i++)
	{
		GotoxyPreparePrintMenu(i);
		if (Skills->at(i)->GetType() != 0)
		{
			cout << "#" << i + 1 << " " << Skills->at(i)->GetName() << "(" << Skills->at(i)->GetMpConsume() << ")";
		}
		else
		{
			cout << "#" << i + 1 << " " << Skills->at(i)->GetName();
		}
	}
}

void Player::DisplaySkillsDetail()
{
	system("cls");
	GotoxyPreparePrintMenu(-2);
	cout << "<스킬>";
	for (int i = 0;i < Skills->size();i++)
	{
		GotoxyPreparePrintMenu(i * 3);
		GotoxyClsLong(1);
		if (Skills->at(i)->GetType() != 0)
		{
			cout << "#" << i << " " << Skills->at(i)->GetEnhancedName() << " | MP : " << Skills->at(i)->GetMpConsume();
		}
		else
		{
			cout << "#" << i << " " << Skills->at(i)->GetEnhancedName();
		}
		GotoxyPreparePrintMenu(i * 3 + 1);
		GotoxyClsLong(1);
		cout << Skills->at(i)->GetExplanation();
	}
}

bool Player::UseSkill(shared_ptr<Creature> creature, int num, int turn)
{
	string message = Skills->at(num)->Effect(creature, turn);
	if (!message.empty())
	{

		if (message == "-1")
		{
			return false;
		}
		else
		{
			AddNotification(message);
		}
	}
	return true;
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
