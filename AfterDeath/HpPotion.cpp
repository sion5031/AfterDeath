#include "HpPotion.h"

HpPotion::HpPotion(int num)
{
	Number = num;
	this->SetName("Hp ����");
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
