#include "HpPotion.h"

HpPotion::HpPotion()
{
	this->SetName("Hp Æ÷¼Ç");
	this->SetSN(20);
	this->EffectPoint = 10;
}

HpPotion::~HpPotion()
{
}

void HpPotion::UseItem(shared_ptr<Creature> player)
{
	player->CalcHp(this->EffectPoint);
}
