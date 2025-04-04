#include "HpPotion.h"

HpPotion::HpPotion(int num)
{
	Number = num;
	this->SetName("Hp 포션");
	this->SetSN(20);
	this->EffectPoint = 10;
}

HpPotion::~HpPotion()
{
}

void HpPotion::UseItem(shared_ptr<Creature> player)
{
	player->CalcHp(this->EffectPoint);
	Number--; // consumable에서 하고싶어...
	if (Number <= 0)
	{
		Number = 0;
	}
}
