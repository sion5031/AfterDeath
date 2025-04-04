#include "MpPotion.h"

MpPotion::MpPotion(int num)
{
	Number = num;
	this->SetName("Mp ����");
	this->SetSN(21);
	this->EffectPoint = 10;
}

MpPotion::~MpPotion()
{
}

void MpPotion::UseItem(shared_ptr<Creature> player)
{
	player->CalcMp(this->EffectPoint);
}
