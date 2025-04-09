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


Monster::Monster()
{
	Name = "스켈레톤";
	Type = 1;
	MaxHp = 20;
	MaxMp = 5;
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
	MaxHp = 200;
	MaxMp = 800;
	Attack = 35;
	Defense = 10;
	Items = new vector<Item*>;
	Skills = new vector<Skill*>;
	//Equipments = new EquipedE; //Creature 생성자에서 생성

	Equipments->myWeapon = new LongSword(level);
	Equipments->myUpper = new Upper(level);
	Equipments->myLower = new Lower(level);
	Equipments->myGlove = new Glove(level);
	Equipments->myShoes = new Shoes(level);
	Equipments->myShield = new Shield(level);

	Skill* fireBall = new FireBall(level);
	Skill* increaseAttack = new IncreaseAttack(level);
	Skill* defenseUp = new DefenseUp(2 + level);

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
		int num = rand() % (int)(this->Skills->size()); //스킬 사이즈 0 예외?
		cout << this->Skills->at(num)->GetName() << " 사용" << endl;
		creature->CalcHp(-this->Skills->at(num)->GetEffectValue());
	}
	return true;
}

void Monster::Die()
{
}