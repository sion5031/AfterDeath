#include "AttackUp.h"

AttackUp::AttackUp()
{
	Name = "공격력 증가";
	Type = 0;
	EffectValue = 3;
	Level = 1;
}

string AttackUp::Effect(shared_ptr<Creature> player, int turn)
{
	return nullptr;
}
