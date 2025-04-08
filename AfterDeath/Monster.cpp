#include "Monster.h"
#include "LongSword.h"
#include "ShortSword.h"
#include "Upper.h"
#include "Lower.h"
#include "Glove.h"
#include "Shoes.h"
#include "Shield.h"


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

	Equipments->myWeapon = new LongSword();
	Equipments->myUpper = new Upper();
	Equipments->myLower = new Lower();
	Equipments->myGlove = new Glove();
	Equipments->myShoes = new Shoes();
	Equipments->myShield = new Shield();

	Hp = GetTotalStatus()->TotalMaxHp;
	Mp = GetTotalStatus()->TotalMaxMp;
}

Monster::Monster(int level)
{
	Name = "드래곤";
	Type = 1;
	MaxHp = 200;
	Hp = MaxHp;
	MaxMp = 800;
	Mp = MaxMp;
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