#include "Player.h"

void Player::UseItem(int num)
{
}

void Player::EquipItem(int num)
{
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
	Equipments = new struct EquipedE;
	Skills = new vector<Skill*>;
	
	DeathCount = 0;
	MyInven = new Inventory();

	cout << "캐릭터를 생성했습니다." << endl;
}

Player::Player(string name)
{
	Name = name;
	Type = 1;
	MaxHp = 100;
	Hp = MaxHp;
	MaxMp = 50;
	Mp = MaxMp;
	Attack = 10;
	Defense = 5;
	Equipments = new struct EquipedE;
	Skills = new vector<Skill*>;

	DeathCount = 0;
	MyInven = new Inventory();
}

Player::~Player()
{
}

void Player::DisplayInventory()
{
}

void Player::AddInventory(Item*)
{
}

void Player::SelectInventoryItem(int num)
{
}

void Player::AddSkill(Skill* skill)
{
}

void Player::PlusDeathCount(int num)
{
}

void Player::UseSkill()
{
}

void Player::Die()
{
}

void Player::SetDeathCount(int deathCount)
{
}

int Player::GetDeathCount()
{
	return 0;
}
