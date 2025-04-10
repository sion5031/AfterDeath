#include "Monster.h"
#include "LongSword.h"
#include "ShortSword.h"
#include "Upper.h"
#include "Lower.h"
#include "Glove.h"
#include "Shoes.h"
#include "Shield.h"
#include "FireBall.h"
#include "IncreaseAttack.h"
#include "AttackUp.h"
#include "DefenseUp.h"
#include "LichHead.h"


Monster::Monster()
{
	Name = "스켈레톤";
	Type = 1;
	MaxHp = 20;
	MaxMp = 15;
	Attack = 15;
	Defense = 3;
	Items = new vector<Item*>;
	Skills = new vector<Skill*>;
	//Equipments = new EquipedE; //Creature 생성자에서 생성

	int randomEquip = rand() % 6;

	if (randomEquip % 3 == 0)
	{
		Equipments->myWeapon = new LongSword();
		Equipments->myGlove = new Glove();
	}
	if (randomEquip % 3 == 0)
	{
		Equipments->myWeapon = new ShortSword();
		Equipments->myShield = new Shield();
	}
	else if (randomEquip % 3 == 0)
	{
		Equipments->myWeapon = new ShortSword();
		Equipments->myUpper = new Upper();
	}
	else
	{
		Equipments->myLower = new Lower();
		Equipments->myShoes = new Shoes();
	}

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

Monster::Monster(int level)
{
	Name = "드래곤";
	Type = 1;
	MaxHp = 150;
	MaxMp = 800;
	Attack = 35;
	Defense = 10;
	Items = new vector<Item*>;
	Skills = new vector<Skill*>;
	//Equipments = new EquipedE; //Creature 생성자에서 생성

	Equipments->myWeapon = new LongSword(level);
	Equipments->myUpper = new Upper(level);
	Equipments->myLower = new Lower(level);
	//Equipments->myGlove = new Glove(level);
	Equipments->myShoes = new Shoes(level);
	Equipments->myShield = new Shield(level);

	Skill* fireBall = new FireBall(level);
	Skill* increaseAttack = new IncreaseAttack(level);
	Skill* defenseUp = new DefenseUp(1 + level);
	if (level == 2)
	{
		Equipments->myGlove = new LichHead();
	}

	Skills->push_back(fireBall);
	Skills->push_back(increaseAttack);
	Skills->push_back(defenseUp);


	Hp = GetTotalStatus()->TotalMaxHp;
	Mp = GetTotalStatus()->TotalMaxMp;
}

Monster::~Monster()
{
}

void Monster::SetItems(vector<Item*>* equipments)
{
	Items = Items;
}

bool Monster::UseSkill(shared_ptr<Creature> creature, int num, int count)
{
	if (this->Skills->size() > 0)
	{
		int ran = rand() % (int)(this->Skills->size());
		Skill* currentSkill = Skills->at(ran);
		if (currentSkill->GetType() == 1 && this->Mp >= currentSkill->GetMpConsume()) // 액티브 공격만
		{
			CalcMp(-currentSkill->GetMpConsume());
			int before = creature->GetHp();
			AddNotification(Name + " 가 " + currentSkill->GetName() + " 을 사용했습니다.");
			Skills->at(ran)->Effect(creature, count);
			int after = creature->GetHp();
			AddNotification(creature->GetName() + " 가 " + to_string(before - after) + " 만큼의 피해를 입었습니다.");
		}
		else
		{
			AddNotification(Name + " 가 " + " 스킬 사용에 실패했습니다.");
		}
	}
	return true;
}

void Monster::Die()
{
}