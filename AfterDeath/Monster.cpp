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
	Name = "고블린";
	Type = 1;
	MaxHp = 20;
	Hp = MaxHp;
	MaxMp = 5;
	Mp = MaxMp;
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
}

Monster::~Monster()
{
}

void Monster::SetItems(vector<Item*>* equipments)
{
	Items = Items;
}

void Monster::UseSkill(shared_ptr<Creature> creature)
{
	if (this->Skills->size() > 0)
	{
		int num = rand() % (int)(this->Skills->size()); //스킬 사이즈 0 예외?
		cout << this->Skills->at(num)->GetName() << " 사용" << endl;
		creature->CalcHp(-this->Skills->at(num)->GetEffectValue());
	}
}

void Monster::Die()
{
}

//int Monster::GetTotalAtk()
//{
//	int sum = Attack;
//
//	if (Equipments->myWeapon != nullptr)
//	{
//		sum += Equipments->myWeapon->GetAtkPoint();
//	}
//	if (Equipments->myWeapon != nullptr)
//	{
//		sum += Equipments->myWeapon->GetAtkPoint();
//	}
//	if (Equipments->myWeapon != nullptr)
//	{
//		sum += Equipments->myWeapon->GetAtkPoint();
//	}
//	if (Equipments->myWeapon != nullptr)
//	{
//		sum += Equipments->myWeapon->GetAtkPoint();
//	}
//	if (Equipments->myWeapon != nullptr)
//	{
//		sum += Equipments->myWeapon->GetAtkPoint();
//	}
//	if (Equipments->myWeapon != nullptr)
//	{
//		sum += Equipments->myWeapon->GetAtkPoint();
//	}
//
//	return sum;
//}
//
//int Monster::GetTotalDef()
//{
//	int sum = Defense;
//	for (int i = 0;i < Equipments->size();i++)
//	{
//		sum += Equipments->at(i)->GetDefPoint();
//	}
//	return sum;
//}
//
//int Monster::GetTotalMaxHp()
//{
//	int sum = MaxHp;
//	for (int i = 0;i < Equipments->size();i++)
//	{
//		sum += Equipments->at(i)->GetHpPoint();
//	}
//	return sum;
//}
//
//int Monster::GetTotalMaxMp()
//{
//	int sum = MaxMp;
//	for (int i = 0;i < Equipments->size();i++)
//	{
//		sum += Equipments->at(i)->GetMpPoint();
//	}
//	return sum;
//}
