#include "Player.h"

void Player::UseItem(int num, shared_ptr<Creature> player)
{
	MyInven->TryUse(num, player);
}

void Player::EquipItem(int num)
{
	MyInven->TryEquip(num);
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
	
	DeathCount = 0;
	MyInven = new Inventory();

	cout << "캐릭터를 생성했습니다." << endl;
}

Player::Player(string name)
{
	Name = name;
	Type = 0;
	MaxHp = 100;
	Hp = MaxHp;
	MaxMp = 50;
	Mp = MaxMp;
	Attack = 10;
	Defense = 5;
	Skills = new vector<Skill*>;

	DeathCount = 0;
	MyInven = new Inventory();

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

int Player::GetTotalAtk()
{
	return MyInven->GetTotalEquipmentAtk() + Attack;
}

int Player::GetTotalDef()
{
	return MyInven->GetTotalEquipmentDef() + Defense;
}

int Player::GetTotalMaxHp()
{
	return MyInven->GetTotalEquipmentMaxHp() + MaxHp;
}

int Player::GetTotalMaxMp()
{
	return MyInven->GetTotalEquipmentMaxMp() + MaxMp;
}
