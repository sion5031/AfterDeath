#include "MpPotion.h"

MpPotion::MpPotion()
{
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
