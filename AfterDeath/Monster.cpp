#include "Monster.h"

Monster::Monster()
{
	Name = "°íºí¸°";
	Type = 1;
	MaxHp = 20;
	Hp = MaxHp;
	MaxMp = 5;
	Mp = MaxMp;
	Attack = 10;
	Defense = 3;
	Equipments = new struct EquipedE;
	Skills = new vector<Skill*>;
}

Monster::~Monster()
{
}

void Monster::UseSkill()
{
}

void Monster::Die()
{
}
